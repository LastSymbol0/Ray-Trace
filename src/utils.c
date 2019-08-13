/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 16:52:21 by aillia            #+#    #+#             */
/*   Updated: 2019/08/13 16:52:23 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	ft_err(char *err, int status)
{
	if (status == 1)
		ft_putstr("Error: ");
	ft_putendl(err);
	exit(status);
}

void	set_tabs(int n)
{
	int i;

	i = -1;
	while (++i < n)
		printf("\t");
}

int		arr_len(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}