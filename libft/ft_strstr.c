/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 11:41:25 by aillia            #+#    #+#             */
/*   Updated: 2018/11/03 16:25:08 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int i;
	int j;
	int g;

	i = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[i] != '\0')
	{
		if (str[i] == to_find[0])
		{
			j = i;
			g = 0;
			while (str[j] == to_find[g])
			{
				if (to_find[g + 1] == '\0')
					return ((char *)&str[i]);
				j++;
				g++;
			}
		}
		i++;
	}
	return (NULL);
}
