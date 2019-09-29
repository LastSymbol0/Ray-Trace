/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_set_h.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 12:30:05 by aillia            #+#    #+#             */
/*   Updated: 2019/09/29 12:30:07 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	set_light(t_scene *sc, xmlNodePtr obj, int i)
{
	xmlNodePtr	child;

	child = obj->children;
	while (child)
	{
		if (child->type == XML_ELEMENT_NODE)
		{
			if (ft_strequ((char *)child->name, "pos"))
				sc->lights[i].pos = parse_vec(
										(char *)xmlNodeGetContent(child));
			else if (ft_strequ((char *)child->name, "intensity"))
				sc->lights[i].intensity = ft_atoi(
										(char *)xmlNodeGetContent(child));
			else if (ft_strequ((char *)child->name, "color"))
				sc->lights[i].color = parse_color(
										(char *)xmlNodeGetContent(child));
			else
				ft_err("Undefined light argument", 1);
		}
		child = child->next;
	}
	sc->lights[i].fcolor = get_fcolor(sc->lights[i].color);
}

void	scene_set_lights(t_scene *sc, xmlNodePtr cur)
{
	int			i;

	i = 0;
	while (cur)
	{
		if (cur->type == XML_ELEMENT_NODE &&
		ft_strequ((char *)cur->name, "light"))
			set_light(sc, cur, i++);
		cur = cur->next;
	}
}
