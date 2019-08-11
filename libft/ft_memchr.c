/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 16:46:56 by aillia            #+#    #+#             */
/*   Updated: 2018/10/27 21:50:41 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p1;
	size_t			i;

	i = -1;
	p1 = (unsigned char *)s;
	while (++i < n)
		if (p1[i] == (unsigned char)c)
			return ((void *)(p1 + i));
	return (NULL);
}
