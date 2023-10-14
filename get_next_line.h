/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduffaut <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:50:00 by cduffaut          #+#    #+#             */
/*   Updated: 2023/10/14 10:30:52 by csil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);
void	create_li(t_list **li, int fd);
void	add_end(t_list **li, char *stock, int count);
void	create_line(t_list *li, char **line);
void	clean_li(t_list **li);
t_list	*ptr_last_node(t_list *li);
int		checker(t_list *li);
void	malloc_line(t_list *li, char **line);
int		ft_strlen(char *str);
void	free_li(t_list **li, t_list *new_node, char *str);

#endif
