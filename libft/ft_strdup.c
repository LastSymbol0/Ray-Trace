/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <aillia@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 15:39:24 by aillia            #+#    #+#             */
/*   Updated: 2018/10/24 12:36:51 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		strlen;
	char	*dup;

	strlen = 0;
	while (src[strlen] != '\0')
		strlen++;
	dup = (char *)malloc(sizeof(char) * (strlen + 1));
	if (dup)
	{
		dup[strlen] = '\0';
		strlen = -1;
		while (src[++strlen] != '\0')
			dup[strlen] = src[strlen];
		return (dup);
	}
	else
		return (NULL);
}
