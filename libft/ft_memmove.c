/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 14:47:23 by aillia            #+#    #+#             */
/*   Updated: 2018/11/03 17:32:46 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t l)
{
	char	*d;
	char	*s;
	size_t	i;

	i = -1;
	d = (char *)dst;
	s = (char *)src;
	if (s < d)
		while ((int)(--l) >= 0)
			*(d + l) = *(s + l);
	else
		while (++i < l)
			*(d + i) = *(s + i);
	return (dst);
}
