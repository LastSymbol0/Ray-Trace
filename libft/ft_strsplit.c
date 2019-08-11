/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 12:12:01 by aillia            #+#    #+#             */
/*   Updated: 2018/11/04 12:51:03 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**create_arr(int size)
{
	char	**res;

	res = (char **)ft_memalloc(sizeof(*res) * (size + 1));
	if (!res)
		return (NULL);
	return (res);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**res;

	if (!s || !(res = create_arr(ft_countwords(s, c))))
		return (NULL);
	i = -1;
	k = -1;
	while (s[++i] != '\0')
	{
		j = i;
		while (s[j] != c && s[j] != '\0')
			j++;
		if (j - i > 0)
		{
			if (!(res[++k] = ft_strnew(j - i)))
				return (NULL);
			res[k] = ft_strncpy(res[k], (s + i), j - i);
			i = j;
		}
		if (s[i] == '\0')
			break ;
	}
	return (res);
}
