/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsusol <vsusol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 19:58:36 by aillia            #+#    #+#             */
/*   Updated: 2019/08/29 18:41:38 by vsusol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

cl_float3	parse_vec(char *s)
{
	cl_float3	v;
	char		**split;

	split = ft_strsplit(s, ',');
	xmlFree(s);
	if (arr_len(split) != 3)
		ft_err("Error reading file", 1);
	v.x = ft_atoi(split[0]);
	v.y = ft_atoi(split[1]);
	v.z = ft_atoi(split[2]);
	free(split[0]);
	free(split[1]);
	free(split[2]);
	free(split);
	return (v);
}

t_color		parse_color(char *s)
{
	t_color			res;
	unsigned int	color;
	unsigned int	color_tmp;

	color = abs(ft_atoi_base(s, 16));
	xmlFree(s);
	color_tmp = color;
	res.blue = equalizer((color_tmp << 24) >> 24, 1, 255);
	color_tmp = color;
	res.green = equalizer((color_tmp << 16) >> 24, 1, 255);
	color_tmp = color;
	res.red = equalizer((color_tmp << 8) >> 24, 1, 255);
	return (res);
}

short		get_type(char *s)
{
	if (ft_strequ(s, "plane"))
		return (PLANE);
	else if (ft_strequ(s, "sphere"))
		return (SPHERE);
	else if (ft_strequ(s, "cylinder"))
		return (CYLINDER);
	else if (ft_strequ(s, "cone"))
		return (CONE);
	else if (ft_strequ(s, "cam"))
		return (CAM);
	else
		ft_err("Undefined object name", 1);
	return (1);
}

int			ft_atoi_free(char *str)
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
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	xmlFree(str);
	return (res * sign);
}