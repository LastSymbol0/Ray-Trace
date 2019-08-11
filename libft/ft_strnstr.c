/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 11:41:25 by aillia            #+#    #+#             */
/*   Updated: 2018/11/03 17:42:47 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	size_t	i;
	size_t	j;
	int		g;

	i = 0;
	if (find[0] == '\0')
		return ((char *)str);
	while (str[i] != '\0' && i <= len - 1)
	{
		if (str[i] == find[0])
		{
			j = i;
			g = 0;
			while (str[j] == find[g] && j <= len)
			{
				if (find[g + 1] == '\0')
					return ((char *)&str[i]);
				j++;
				g++;
			}
		}
		i++;
	}
	return (NULL);
}
