/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 17:46:13 by aillia            #+#    #+#             */
/*   Updated: 2018/10/27 20:55:41 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*s1;

	s1 = (char *)s;
	len = ft_strlen(s1) + 1;
	while (--len >= 0)
		if (s1[len] == c)
			return (s1 + len);
	return (NULL);
}
