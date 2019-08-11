/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 11:01:48 by aillia            #+#    #+#             */
/*   Updated: 2018/10/27 21:22:53 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *destptr, const char *srcptr)
{
	int i;
	int j;

	i = 0;
	j = -1;
	while (destptr[i] != '\0')
		i++;
	while (srcptr[++j] != '\0')
		destptr[i++] = srcptr[j];
	destptr[i] = '\0';
	return (destptr);
}
