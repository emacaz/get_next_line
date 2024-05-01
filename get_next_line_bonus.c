/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcastil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:44:55 by emcastil          #+#    #+#             */
/*   Updated: 2024/04/30 21:44:56 by emcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
* Adds a new node with provided data to the end of a linked list.
*/
void	chain_add_back(t_list **chain, char *line, int fd)
{
	t_list	*new_node;
	t_list	*last_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	last_node = find_last_node(chain[fd]);
	if (new_node == NULL)
		return ;
	if (last_node == NULL)
		chain[fd] = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = line;
	new_node->next = NULL;
}

/*
 * Rearrange chain for next call
*/
void	arrange_chain(t_list **chain)
{
	t_list	*last_node;
	t_list	*empty_node;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	empty_node = malloc(sizeof(t_list));
	if (!buf || !empty_node)
		return ;
	last_node = find_last_node(*chain);
	i = 0;
	k = 0;
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		++i;
	while (last_node->str_buf[i] && last_node->str_buf[++i])
		buf[k++] = last_node->str_buf[i];
	buf[k] = '\0';
	empty_node->str_buf = buf;
	empty_node->next = NULL;
	free_chain(chain, empty_node, buf);
}

/*
* Extracts and returns the first line up to
* a newline character from a linked list of strings.
*/
char	*get_the_line(t_list *chain)
{
	char	*next_string;
	int		s_len;

	if (NULL == chain)
		return (NULL);
	s_len = len_to_newline(chain);
	next_string = (char *)malloc(s_len + 1);
	if (NULL == next_string)
		return (NULL);
	copy_string(chain, next_string);
	return (next_string);
}

/*
* Fills a linked list with data from a file descriptor
* until encountering a newline or end of data.
*/
void	create_chain(t_list **chain, int fd)
{
	char	*buffer;
	int		bytes_read;

	while (!is_newline(chain[fd]))
	{
		buffer = (char *)malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (!bytes_read)
		{
			free(buffer);
			return ;
		}
		buffer[bytes_read] = '\0';
		chain_add_back(chain, buffer, fd);
	}
}

/*
* Receives a fd and returns every \n-ended line
* Limit of 1024 nodes in the chain
*/
char	*get_next_line(int fd)
{
	static t_list	*chain[1024];
	char			*line;

	if (fd == -1 || fd > 1023 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	create_chain(chain, fd);
	if (chain[fd] == NULL)
		return (NULL);
	line = get_the_line(chain[fd]);
	arrange_chain(&chain[fd]);
	return (line);
}

// int	main(void) {
// 	int		fds[3];
// 	int		j;
// 	int		active_fds;
// 	char	*line;

// 	fds[0] = open("file1.txt", O_RDONLY);
// 	fds[1] = open("file2.txt", O_RDONLY);
// 	fds[2] = open("file3.txt", O_RDONLY);
// 	// Check if files open
// 	j = 0;
// 	while (j < 3) {
// 		if (fds[j] == -1) {
// 			printf("Failed to open...");
// 			return (1);
// 		}
// 		j++;
// 	}
// 	// Read and print one line from each file in a round
// 	active_fds = 3;
// 	while (active_fds > 0) {
// 		j = 0;
// 		while (j < 3) {
// 			if (fds[j] != -1) {
// 				line = get_next_line(fds[j]);
// 				if (line == NULL) {
// 					close(fds[j]);
// 					fds[j] = -1;
// 					active_fds--;
// 				}
// 				else {
// 					printf("Files %d: %s\n", j + 1, line);
// 					free(line);
// 				}
// 			}
// 			j++;
// 		}
// 	}
// 	system("leaks a.out");
// 	getchar();
// 	return (0);
// }