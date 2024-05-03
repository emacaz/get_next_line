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
int	create_chain(t_list **chain, int fd)
{
	char	*buffer;
	int		bytes_read;

	while (!is_newline(chain[fd]))
	{
		buffer = (char *)malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return (-1);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (-1);
		}
		if (bytes_read == 0)
		{
			free(buffer);
			return (0);
		}
		buffer[bytes_read] = '\0';
		chain_add_back(chain, buffer, fd);
	}
	return (0);
}

/*
* Receives a fd and returns every \n-ended line
* Limit of 1024 nodes in the chain
*/
char	*get_next_line(int fd)
{
	static t_list	*chain[1024];
	char			*line;
	t_list			*aux;

	if (fd == -1 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	if (create_chain(chain, fd) == -1)
	{
		while (chain[fd])
		{
			aux = (chain[fd])->next;
			free((chain[fd])->str_buf);
			free(chain[fd]);
			chain[fd] = aux;
		}
		chain[fd] = NULL;
	}
	if (chain[fd] == NULL)
		return (NULL);
	line = get_the_line(chain[fd]);
	arrange_chain(&chain[fd]);
	return (line);
}

/*int main(void)
{
	char *file = "file1.txt";
	int fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	int i = 9;
	while (i--)
	{
		char *result = get_next_line(fd);
		printf("Linea %d: %s", i, result);
		free(result);
	}
	close(fd);
	char *file2 = "file2.txt";
	int fd2 = open(file2, O_RDONLY);
	if (fd2 == -1)
		return (0);
	int j = 4;
	while (j--)
	{
		char *result2 = get_next_line(fd);
		printf("Linea %d: %s", j, result2);
		free(result2);
	}
	close(fd2);
	system("leaks -q a.out");
	return (0);
}*/