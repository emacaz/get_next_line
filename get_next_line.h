/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcastil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:28:38 by emcastil          #+#    #+#             */
/*   Updated: 2024/04/28 16:42:07 by emcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
void	chain_add_back(t_list **chain, char *line);
void	create_chain(t_list **chain, int fd);
int		is_newline(t_list *chain);
int		len_to_newline(t_list *list);
void	copy_string(t_list *list, char *str);
void	arrange_chain(t_list **chain);
t_list	*find_last_node(t_list *chain);
void	free_chain(t_list **chain, t_list *empty_node, char *buffer);
char	*get_the_line(t_list *chain);

#endif
