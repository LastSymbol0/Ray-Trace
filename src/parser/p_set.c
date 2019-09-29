/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_set.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsusol <vsusol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 19:55:38 by aillia            #+#    #+#             */
/*   Updated: 2019/08/31 16:15:09 by vsusol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	set_object_h(t_scene *sc, int i, xmlNodePtr child)
{
	if (ft_strequ((char *)child->name, "pos"))
		sc->objects[i].pos = parse_vec((char *)xmlNodeGetContent(child));
	else if (ft_strequ((char *)child->name, "rot"))
		sc->objects[i].rot = v_norm(
								parse_vec((char *)xmlNodeGetContent(child)));
	else if (ft_strequ((char *)child->name, "radius"))
		sc->objects[i].radius = ft_atoi((char *)xmlNodeGetContent(child));
	else if (ft_strequ((char *)child->name, "color"))
		sc->objects[i].color = parse_color((char *)xmlNodeGetContent(child));
	else if (ft_strequ((char *)child->name, "difuse"))
		sc->objects[i].difuse = FROM_0_TO_1(
							ft_atoi((char *)xmlNodeGetContent(child)) / 100.);
	else if (ft_strequ((char *)child->name, "reflection_coef"))
		sc->objects[i].reflection_coef = FROM_0_TO_1(
							ft_atoi((char *)xmlNodeGetContent(child)) / 100.);
	else if (ft_strequ((char *)child->name, "transparency_coef"))
		sc->objects[i].transparency_coef = FROM_0_TO_1(
							ft_atoi((char *)xmlNodeGetContent(child)) / 100.);
	else if (ft_strequ((char *)child->name, "refract_coef"))
		sc->objects[i].refract_coef = ft_atoi(
									(char *)xmlNodeGetContent(child)) / 10.;
	else
		ft_err("Undefined object argument", 1);
}

void	set_object(t_scene *sc, xmlNodePtr obj, int i, short type)
{
	xmlNodePtr	child;

	child = obj->children;
	sc->objects[i].type = type;
	sc->objects[i].refract_coef = 1.0;
	while (child)
	{
		if (child->type == XML_ELEMENT_NODE)
			set_object_h(sc, i, child);
		child = child->next;
	}
	sc->objects[i].fcolor = get_fcolor(sc->objects[i].color);
}

void	scene_set_objects(t_scene *sc, xmlNodePtr root)
{
	int			i;
	xmlNodePtr	cur;

	i = 0;
	cur = root->children;
	while (cur)
	{
		if (cur->type == XML_ELEMENT_NODE &&
		!ft_strequ((char *)cur->name, "light") &&
		!ft_strequ((char *)cur->name, "cam"))
			set_object(sc, cur, i++, get_type((char *)cur->name));
		cur = cur->next;
	}
}

void	scene_set_cam_h(t_scene *sc, xmlNodePtr child)
{
	if (child->type == XML_ELEMENT_NODE)
	{
		if (ft_strequ((char *)child->name, "pos"))
			sc->cam.pos = parse_vec((char *)xmlNodeGetContent(child));
		else if (ft_strequ((char *)child->name, "rot"))
			sc->cam.rot = parse_vec((char *)xmlNodeGetContent(child));
	}
}

int		scene_set_cam(t_scene *sc, xmlNodePtr cur)
{
	xmlNodePtr	child;
	int			n;

	n = 0;
	while (cur)
	{
		if (cur->type == XML_ELEMENT_NODE &&
							ft_strequ((char *)cur->name, "cam"))
		{
			child = cur->children;
			while (child)
			{
				scene_set_cam_h(sc, child);
				child = child->next;
			}
			n++;
		}
		cur = cur->next;
	}
	return (n);
}
