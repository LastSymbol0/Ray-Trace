/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 18:38:29 by aillia            #+#    #+#             */
/*   Updated: 2018/11/03 18:48:34 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*str;

	size++;
	i = -1;
	str = (char *)malloc(sizeof(char) * size);
	if (str)
	{
		while (++i <= size)
			str[i] = '\0';
		return (str);
	}
	return (NULL);
}
