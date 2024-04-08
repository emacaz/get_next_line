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

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif


// allocate memory
// Read the file
// save the string into index of pointer
// Save string '\0' -> *[string1][string2][stringn][NULL]
// free memory

// Returns a read-line from a fd
char	*get_next_line(int fd)
{
	size_t	i;
	ssize_t	bytes_read;
	char	*database;

	database = malloc(BUFFER_SIZE);
	if (!database)
		return (NULL);
	i = 0;
	while (i < BUFFER_SIZE)
	{
		bytes_read = read(fd, &database[i], 1);
		if (bytes_read == -1)
			return (NULL);
		else if (bytes_read == '\n')
			break ;
		i++;
	}
	database[i] = '\0';
	return (database);
}

int	main(int argc, char *argv[])
{
	int		fd;
	char	*first_line;

	if (argc != 2)
	{
		printf("Error at args in main function");
		return (0);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file");
		return (0);
	}

	first_line = get_next_line(fd);
	if (first_line != NULL)
	{
		printf("First line: %s\n", first_line);
		free(first_line);
	}
	close(fd);
	return (1);
}