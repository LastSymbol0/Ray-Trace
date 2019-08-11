/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 19:12:58 by aillia            #+#    #+#             */
/*   Updated: 2018/11/03 19:35:55 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*str;

	i = -1;
	if (s && f)
	{
		str = (char *)malloc(sizeof(char) * ft_strlen((char *)s) + 1);
		if (str)
		{
			while (s[++i])
				str[i] = f(i, s[i]);
			str[i] = '\0';
			return (str);
		}
	}
	return (NULL);
}
