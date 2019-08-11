/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 17:23:10 by aillia            #+#    #+#             */
/*   Updated: 2018/11/19 17:38:55 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	d_size;
	size_t	s_len;
	size_t	i;

	d_size = ft_strlen(dest);
	s_len = ft_strlen((char *)src);
	i = d_size - 1;
	if (size < d_size)
		return (size + ft_strlen((char *)src));
	if (size > d_size)
	{
		while (++i < s_len + d_size && i < size - 1)
			dest[i] = src[i - d_size];
		while (i < size)
			dest[i++] = '\0';
	}
	return (d_size + ft_strlen((char *)src));
}
