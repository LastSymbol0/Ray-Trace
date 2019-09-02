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

t_vec	parse_vec(char *s)
{
	t_vec	v;
	char	**split;

	split = ft_strsplit(s, ',');
	if (arr_len(split) != 3)
		ft_err(ft_strjoin("Error reading, fragment: ", s), 1);
	v.x = ft_atoi(split[0]);
	v.y = ft_atoi(split[1]);
	v.z = ft_atoi(split[2]);
	free(split[0]);
	free(split[1]);
	free(split[2]);
	free(split);
	return (v);
}

t_color	parse_color(char *s)
{
	t_color 		res;
	unsigned int	color;
	unsigned int	color_tmp;

	color = abs(ft_atoi_base(s, 16));
	color_tmp = color;
	res.blue = equalizer((color_tmp << 24) >> 24, 1, 255);
	color_tmp = color;
	res.green = equalizer((color_tmp << 16) >> 24, 1, 255);
	color_tmp = color;
	res.red = equalizer((color_tmp << 8) >> 24, 1, 255);
	return (res);
}

short	get_type(char *s)
{
	if (ft_strequ(s, "plane"))
		return(PLANE);
	else if (ft_strequ(s, "sphere"))
		return(SPHERE);
	else if (ft_strequ(s, "cylinder"))
		return(CYLINDER);
	else if (ft_strequ(s, "cone"))
		return(CONE);
	else if (ft_strequ(s, "cam"))
		return(CAM);
	else
		ft_err(ft_strjoin("Undefined object name: ", s), 1);
	return (1);
}

void	recurs(xmlNodePtr node, int n)
{
	xmlNodePtr	cur;

	cur = node;
	while (cur)
	{
		if (cur->type == XML_ELEMENT_NODE)
		{
			set_tabs(n);
			printf("Node found! Childcount: %lu; Name: %s; ", xmlChildElementCount(cur), cur->name);
			if (n == 2)
				printf("Content: %s;\n", xmlNodeGetContent(cur));
			else
				printf("\n");
		}
		recurs(cur->children, n + 1);
		cur = cur->next;
	}
}