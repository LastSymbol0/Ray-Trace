/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 20:58:29 by aillia            #+#    #+#             */
/*   Updated: 2018/11/03 21:53:41 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*bespoleznost(void)
{
	char *res;

	res = (char *)malloc(sizeof(char) * 1);
	res[0] = '\0';
	return (res);
}

char		*ft_strtrim(char const *s)
{
	int		k;
	int		j;
	int		i;
	char	*copy;

	k = 0;
	i = 0;
	if (!s)
		return (NULL);
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	if (s[i] == '\0')
		return (bespoleznost());
	i--;
	j = ft_strlen((char *)s) - 1;
	while (s[j] == ' ' || s[j] == '\n' || s[j] == '\t')
		j--;
	j++;
	if (!(copy = (char *)malloc(sizeof(char) * (j - i))))
		return (NULL);
	while (++i < j)
		copy[k++] = s[i];
	copy[k] = '\0';
	return (copy);
}
