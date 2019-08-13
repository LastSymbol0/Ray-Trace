/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 17:40:41 by aillia            #+#    #+#             */
/*   Updated: 2019/07/05 17:40:45 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

int			ft_atoi_base(char *str, int base)
{
	int i;
	int res;
	int sign;

	i = 0;
	res = 0;
	sign = 1;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] != '\0' && (ft_isdigit(str[i]) || ft_isalpha(str[i])))
	{
		res = res * base + (ft_isdigit(str[i]) ?
									(str[i] - '0') : (str[i] - 'a' + 10));
		i++;
	}
	return ((res == 0 ? 1 : res) * sign);
}
