/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvillasa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 21:33:01 by hvillasa          #+#    #+#             */
/*   Updated: 2016/12/23 01:36:13 by hvillasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*link;
	void	*cont;

	if (!(link = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		link->content = NULL;
		link->content_size = 0;
	}
	else
	{
		if (!(cont = (void *)malloc(content_size)))
			return (NULL);
		ft_memcpy(cont, content, content_size);
		link->content = cont;
		link->content_size = content_size;
	}
	link->next = NULL;
	return (link);
}
