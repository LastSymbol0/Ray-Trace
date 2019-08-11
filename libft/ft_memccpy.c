/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 16:26:10 by aillia            #+#    #+#             */
/*   Updated: 2018/10/27 22:46:05 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	i = -1;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (++i < n)
	{
		d[i] = s[i];
		if (s[i] == (unsigned char)c)
			return (d + i + 1);
	}
	return (NULL);
}
