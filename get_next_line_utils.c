/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emcastil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:28:50 by emcastil          #+#    #+#             */
/*   Updated: 2024/04/28 16:51:08 by emcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Check for a \n character
int	is_newline(t_list *chain)
{
	int	i;

	if (chain == NULL)
		return (0);
	while (chain)
	{
		i = 0;
		while (chain->str_buf && i < BUFFER_SIZE)
		{
			if (chain->str_buf[i] == '\n')
				return (1);
			i++;
		}
		chain = chain->next;
	}
	return (0);
}

/*
 * find the len to new line in
 * a linked list
*/
int	len_to_newline(t_list *list)
{
	int	i;
	int	len;

	if (NULL == list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			if (list->str_buf[i] == '\n')
			{
				++len;
				return (len);
			}
			++i;
			++len;
		}
		list = list->next;
	}
	return (len);
}

/*
* Copy characters from a linked list of string buffers
* into a single string
*/
void	copy_string(t_list *chain, char *str)
{
	int	i;
	int	j;

	if (NULL == chain)
		return ;
	j = 0;
	while (chain)
	{
		i = 0;
		while (chain->str_buf[i])
		{
			if (chain->str_buf[i] == '\n')
			{
				str[j++] = '\n';
				str[j] = '\0';
				return ;
			}
			str[j++] = chain->str_buf[i++];
		}
		chain = chain->next;
	}
	str[j] = '\0';
}

/*
* Find the last node of a chain
*/
t_list	*find_last_node(t_list *chain)
{
	if (NULL == chain)
		return (NULL);
	while (chain->next)
		chain = chain->next;
	return (chain);
}

void	free_chain(t_list **chain, t_list *empty_node, char *buffer)
{
	t_list	*temp;

	if (*chain == NULL)
		return ;
	while (*chain)
	{
		temp = (*chain)->next;
		free((*chain)->str_buf);
		free(*chain);
		*chain = temp;
	}
	*chain = NULL;
	if (empty_node->str_buf[0])
		*chain = empty_node;
	else
	{
		free(buffer);
		free(empty_node);
	}
}
