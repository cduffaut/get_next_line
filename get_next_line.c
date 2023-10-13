/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduffaut <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:49:40 by cduffaut          #+#    #+#             */
/*   Updated: 2023/10/13 18:09:13 by csil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

/* Main function */

char	*get_next_line(int fd)
{
	static t_list	*li = NULL;
	char			*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, line, 0) < 0)
		return (NULL);
	line = NULL;
	create_li(&li, fd);
	if (!li)
		return (NULL);
	create_line(li, &line);
	clean_li(&li);
	if (line[0] == '\0')
	{
		clean_li(&li);
		free (line);
		line = NULL;
	}
	return (line);
}

/* Read the line until \n or the end end add it to the list */

void	create_li(t_list **li, int fd)
{
	int		count;
	char	*stock;

	count = 1;
	while (checker(*li) == 0 && count != 0)
	{
		stock = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!stock)
			return ;
		count = read(fd, stock, BUFFER_SIZE);
		if ((!(*li) && count == 0) || count == -1)
		{
			free (stock);
			return ;
		}
		stock[count] = '\0';
		add_end(li, stock, count);
		free (stock);
	}
}

/* Create a node fill it with the line and add it to the list */

void	add_end(t_list **li, char *stock, int count)
{
	t_list	*new_node;
	t_list	*tmp;
	int		i;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->str = malloc(sizeof(char) * (count + 1));
	if (!new_node->str)
		return ;
	new_node->next = NULL;
	i = 0;
	while (stock[i] && i < count)
	{
		new_node->str[i] = stock[i];
		i++;
	}
	new_node->str[i] = '\0';
	if (!(*li))
	{
		*li = new_node;
		return ;
	}
	tmp = ptr_last_node(*li);
	tmp->next = new_node;
}

/* Create the line that we will return by allocating it first */

void	create_line(t_list *li, char **line)
{
	int	i;
	int	j;

	if (!(li))
		return ;
	malloc_line(li, line);
	if (!line)
		return ;
	j = 0;
	while (li)
	{
		i = 0;
		while (li->str[i])
		{
			if (li->str[i] == '\n')
			{
				(*line)[j++] = li->str[i];
				break ;
			}
			(*line)[j++] = li->str[i++];
		}
		li = li->next;
	}
	(*line)[j] = '\0';
}

/* 
	Furfill a new node with the "rest" 
	And then free the list
	Put the fresh node in the list
*/

void	clean_li(t_list **li)
{
	t_list	*new_node;
	t_list	*tmp;
	int		i;
	int		j;

	new_node = malloc(sizeof(t_list));
	if (!new_node || !(*li))
		return ;
	i = 0;
	tmp = ptr_last_node(*li);
	while (tmp->str[i] && tmp->str[i] != '\n')
		i++;
	if (tmp->str[i] && tmp->str[i] == '\n')
		i++;
	new_node->str = malloc(sizeof(char) * (ft_strlen(tmp->str) - i + 1));
	if (!new_node->str)
		return ;
	new_node->next = NULL;
	j = 0;
	while (tmp->str[i])
		new_node->str[j++] = tmp->str[i++];
	new_node->str[j] = '\0';
	free_li(li);
	*li = new_node;
}
/*
int	main(int argc, char **argv)
{
	int		fd;
	char	*str;
	(void) argc;

	fd = open(argv[1], 'r');
	if (fd < 0)
		return (0);
	while (1)
	{
		str = get_next_line(fd);
		printf ("%s", str);
		if (!str)
		{
			free(str);
			break;
		}
		free(str);
	}
	close (fd);
	return (0);
}*/
