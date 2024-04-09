/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcastil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:28:26 by emcastil          #+#    #+#             */
/*   Updated: 2024/04/06 15:28:30 by emcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Returns a read-line from a fd
char	*get_next_line(int fd)
{
	size_t			i;
	ssize_t			bytes_read;
	static char		*database;

	database = malloc(BUFFER_SIZE);
	if (!database)
		return (NULL);
	i = 0;
	while (i < BUFFER_SIZE - 1)
	{
		bytes_read = read(fd, &database[i], 1);
		if (bytes_read == -1)
		{
			free(database);
			return (NULL);
		}
		else if (bytes_read == 0 || database[i] == '\n')
			break ;
		i++;
	}
	database[i] = '\0';
	return (database);
}

int	main(int argc, char *argv[])
{
	int		fd;
	char	*next_line;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			return (printf("Error at opening file"), 1);
	}
	else if (argc == 1)
		fd = STDIN_FILENO;
	else
		return (printf("Error here"), 1);
	next_line = get_next_line(fd);
	if (next_line)
	{
		printf("%s", next_line);
		free(next_line);
	}
	if (argc == 2)
		close(fd);
	return (0);
}
