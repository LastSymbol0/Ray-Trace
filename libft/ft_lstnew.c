/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 20:55:05 by aillia            #+#    #+#             */
/*   Updated: 2018/11/04 20:55:09 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *new_list;

	if (!(new_list = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new_list->next = NULL;
	if (content == NULL)
	{
		new_list->content = NULL;
		new_list->content_size = 0;
		return (new_list);
	}
	if (!(new_list->content = malloc(content_size)))
		return (NULL);
	new_list->content_size = content_size;
	ft_memcpy(new_list->content, (void *)content, content_size);
	return (new_list);
}
