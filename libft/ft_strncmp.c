/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <aillia@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 13:52:35 by aillia            #+#    #+#             */
/*   Updated: 2018/10/30 14:16:59 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;
	char	*s1;
	char	*s2;

	i = -1;
	s1 = (char *)str1;
	s2 = (char *)str2;
	while (*s1 != '\0' && *s2 == *s1 && ++i < n - 1)
	{
		s1++;
		s2++;
	}
	if (n != 0)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	return (0);
}
