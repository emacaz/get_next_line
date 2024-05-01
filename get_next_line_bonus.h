/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcastil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:45:14 by emcastil          #+#    #+#             */
/*   Updated: 2024/04/30 21:45:20 by emcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 84
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
void	create_chain(t_list **chain, int fd);
char	*get_the_line(t_list *chain);
void	arrange_chain(t_list **chain);
t_list	*find_last_node(t_list *chain);
void	free_chain(t_list **chain, t_list *empty_node, char *buffer);
int		len_to_newline(t_list *list);
void	copy_string(t_list *chain, char *str);
int		is_newline(t_list *chain);

#endif