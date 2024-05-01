/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcastil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:34:25 by emcastil          #+#    #+#             */
/*   Updated: 2024/04/28 17:16:42 by emcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	if (NULL == buf || NULL == empty_node)
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
* Adds a new node with provided data to the end of a linked list.
*/
void	chain_add_back(t_list **chain, char *line)
{
	t_list	*new_node;
	t_list	*temp;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->str_buf = line;
	new_node->next = NULL;
	if (*chain == NULL)
	{
		*chain = new_node;
	}
	else
	{
		temp = *chain;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}

/*
* Fills a linked list with data from a file descriptor
* until encountering a newline or end of data.
*/
void	create_chain(t_list **chain, int fd)
{
	char	*buffer;
	int		bytes_read;

	while (!is_newline(*chain))
	{
		buffer = (char *)malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (!bytes_read)
		{
			free(buffer);
			return ;
		}
		buffer[bytes_read] = '\0';
		chain_add_back(chain, buffer);
	}
}

/* Receives a fd and returns every \n-ended line */
char	*get_next_line(int fd)
{
	static t_list	*chain = NULL;
	char			*line;

	if (fd == -1 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	create_chain(&chain, fd);
	if (chain == NULL)
		return (NULL);
	line = get_the_line(chain);
	arrange_chain(&chain);
	return (line);
}

// int main(int argc, char *argv[]) {
// 	int fd;
// 	char *line;

// 	if (argc != 2) {
// 		printf("Usage: %s <filename>\n", argv[0]);
// 		return 1;
// 	}
// 	// Open the file specified by the user
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd == -1) {
// 		perror("Error opening file");
// 		return 1;
// 	}
// 	while ((line = get_next_line(fd)) != NULL) {
// 		printf("%s", line);
// 		free(line); 
// 	}
// 	// Close the file descriptor
// 	close(fd);
// 	system("leaks a.out");
// 	return 0;
// }