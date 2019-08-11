/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 19:49:30 by aillia            #+#    #+#             */
/*   Updated: 2018/11/03 20:05:22 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = -1;
	if (s)
	{
		str = ft_strnew(len);
		if (str)
		{
			while (++i < len)
				str[i] = s[start++];
			return (str);
		}
	}
	return (NULL);
}
