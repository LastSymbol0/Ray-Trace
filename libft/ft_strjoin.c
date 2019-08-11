/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 20:10:02 by aillia            #+#    #+#             */
/*   Updated: 2018/11/03 20:56:03 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;

	if (s1 && s2)
	{
		res = ft_strdup((char *)s1);
		if (res)
		{
			res = ft_strcat(res, s2);
			if (res)
				return (res);
		}
	}
	return (NULL);
}
