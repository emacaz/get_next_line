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

#define BUFFER_SIZE 0

// Returns a read-line from a fd
char	*get_next_line(int fd)
{
	return (0);
}

int	main(void)
{
	int		fd;
	size_t	i;
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	int		found_newline = 0;

	fd = open("file.ecz", O_RDONLY);
	if (fd == -1)
	{
		perror("Error at opening.");
		return (0);
	}

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == - 1)
	{
		perror("Error at reading file.");
		close(fd);
		return (0);
	}

	buffer[bytes_read] = '\0';

	printf("%s", buffer);

	close(fd);
	return (0);
}