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

// Receives a fd and returns the length of bytes
size_t	read_file(int fd)
{
	ssize_t	bytes_read;
	ssize_t	total_length;
	char	*total_char;

	total_length = 0;
	total_char = NULL;
	while ((bytes_read = read(fd, total_char, BUFFER_SIZE)) > 0)
		total_length += bytes_read;
	if (bytes_read == -1)
		total_length = -1;
	return (total_length);
}

// Returns a read-line from a fd
// char	*get_next_line(int fd)
// {
// 	size_t	db_length;

// 	db_length = read_file(fd);

// 	size_t			i;
// 	ssize_t			bytes_read;
// 	static char		*database;

// 	database = (char *)malloc(sizeof(char) * BUFFER_SIZE);
// 	// I can't allocate BUFER_SIZE. What if is 1?
// 	if (!database)
// 		return (NULL);
// 	i = 0;
// 	while (i < BUFFER_SIZE)
// 	{
// 		bytes_read = read(fd, database, BUFFER_SIZE);
// 		if (bytes_read == -1)
// 		{
// 			free(database);
// 			return (NULL);
// 		}
// 		if (database[i] == '\n')
// 		{
// 			i++;
// 			break ;
// 		}
// 		i++;
// 	}
// 	database[i] = '\0';
// 	return (database);
// }

int	main(int argc, char *argv[])
{
	int		fd;
	// char	*next_line2;
	ssize_t	file_length;

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
	file_length = read_file(fd);
	if (file_length)
	{
		printf("%zd", file_length);
		// free(next_line);
	}
	if (argc == 2)
		close(fd);

	// next_line2 = get_next_line(fd);
	// if (next_line2)
	// {
	// 	printf("%s", next_line2);
	// 	free(next_line2);
	// }
	if (argc == 2)
		close(fd);
	return (0);
}