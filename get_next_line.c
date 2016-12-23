/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvillasa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 14:51:32 by hvillasa          #+#    #+#             */
/*   Updated: 2016/12/23 02:04:08 by hvillasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list		*get_fd(int fd)
{
	static t_list	*head;
	t_list			*tmp;

	tmp = head;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", 1);
	tmp->content_size = fd;
	ft_lstadd(&head, tmp);
	return (tmp);
}

static void			merge(t_list *l, char const *buf, int size)
{
	char			*c;

	if (!(l->content))
	{
		l->content = ft_strndup(buf, size);
		return ;
	}
	c = l->content;
	l->content = ft_strjoin(c, buf);
	free((void*)buf);
}

static int			delim_sp(char *s)
{
	int				i;

	i = 0;
	while (s[i] != 0 &&  s[i] != '\n')
		i++;
	return (i);
}

static void			check_z(t_list *n, int ret, char *tmp, int len)
{
	if (ret == 0 && tmp[len] == 0)
		ft_strclr((char*)n->content);
}

int					get_next_line(const int fd, char **line)
{
	int				len;
	int				ret;
	char			*tmp;
	char			buf[BUF_SIZE];
	t_list			*n;

	len = 0;
	ret = 0;
	if (fd < 0 || !(line) ||read(fd, buf, 0) < 0)
		return (-1);
	n = get_fd(fd);
	while (!ft_strchr(buf, '\n') && (ret = read(fd, buf, BUF_SIZE)))
		merge(n, ft_strndup(buf, ret), ret);
	if (ret < BUF_SIZE && ft_strlen(n->content) == 0)
	{
		ft_strclr(*line);
		return (0);
	}
	tmp = n->content;
	len = delim_sp(tmp);
	*line = (tmp[len] == '\n') ? ft_strndup(tmp, len) : ft_strdup(n->content);
	check_z(n, ret, tmp, len);
	n->content = (tmp[len] == '\n') ?
		(ft_strdup(n->content + (len + 1))) : (n->content);
	return (1);
}
