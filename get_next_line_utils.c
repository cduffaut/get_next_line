/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduffaut <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:49:49 by cduffaut          #+#    #+#             */
/*   Updated: 2023/10/14 14:03:39 by csil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Return a pointer to the last node of the list */

t_list	*ptr_last_node(t_list *li)
{
	if (!li)
		return (NULL);
	while (li->next)
	{
		li = li->next;
	}
	return (li);
}

/* Check if there is a '\n' in the list */

int	checker(t_list *li)
{
	int		i;
	t_list	*tmp;

	if (!li)
		return (0);
	tmp = ptr_last_node(li);
	i = 0;
	while (tmp->str[i])
	{
		if (tmp->str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

/* Count the len of the chars until '\n' or (the end) and malloc it */

void	malloc_line(t_list *li, char **line)
{
	int	i;
	int	len;

	len = 0;
	while (li)
	{
		i = 0;
		while (li->str[i])
		{
			if (li->str[i] == '\n')
			{
				len++;
				break ;
			}
			i++;
			len++;
		}
		li = li->next;
	}
	(*line) = malloc(sizeof(char) * (len + 1));
}

/* Return the len of the string */

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

/* 
	Free all of the nodes of the list
*/

void	free_li(t_list **li, t_list *new_node, char *str)
{
	t_list	*tmp;

	if (NULL == *li)
		return ;
	while (*li)
	{
		tmp = (*li)->next;
		free((*li)->str);
		free(*li);
		*li = tmp;
	}
	*li = NULL;
	if (new_node->str[0])
		*li = new_node;
	else
	{
		free(str);
		free(new_node);
	}
}
