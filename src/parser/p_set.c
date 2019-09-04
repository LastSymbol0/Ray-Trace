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

void	set_object(t_scene *sc, xmlNodePtr obj, int i, short type)
{
	xmlNodePtr	child;

	child = obj->children;
	sc->objects[i].type = type;
	while (child)
	{
		if (child->type == XML_ELEMENT_NODE)
		{
			if (ft_strequ((char *)child->name, "pos"))
				sc->objects[i].pos = parse_vec((char *)xmlNodeGetContent(child));
			else if (ft_strequ((char *)child->name, "rot"))
				sc->objects[i].rot = v_norm(parse_vec((char *)xmlNodeGetContent(child)));
			else if (ft_strequ((char *)child->name, "radius"))
				sc->objects[i].radius = ft_atoi((char *)xmlNodeGetContent(child));
			else if (ft_strequ((char *)child->name, "color"))
				sc->objects[i].color = parse_color((char *)xmlNodeGetContent(child));
			else if (ft_strequ((char *)child->name, "difuse"))
				sc->objects[i].difuse = LOWER_THEN_1(ft_atoi((char *)xmlNodeGetContent(child)) / 100.);
			else
				ft_err(ft_strjoin("Undefined object argument: ", (char *)child->name), 1);
		}
		child = child->next;
	}
	sc->objects[i].reflection_coef = 0.4;
	sc->objects[i].reflection_count = 0;
	// if (type == PLANE)
		sc->objects[i].reflection_count = 2;
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

int		scene_set_cam(t_scene *sc, xmlNodePtr cur)
{
	xmlNodePtr	child;
	int			n;

	n = 0;
	while (cur)
	{
		if (cur->type == XML_ELEMENT_NODE && ft_strequ((char *)cur->name, "cam"))
		{
			child = cur->children;
			while (child)
			{
				if (child->type == XML_ELEMENT_NODE)
				{
					if (ft_strequ((char *)child->name, "pos"))
						sc->cam.pos = parse_vec((char *)xmlNodeGetContent(child));
					else if (ft_strequ((char *)child->name, "rot"))
						sc->cam.rot = parse_vec((char *)xmlNodeGetContent(child));
				}
				child = child->next;
			}
			n++;
		}
		cur = cur->next;
	}
	return (n);
}

void	set_light(t_scene *sc, xmlNodePtr obj, int i)
{
	xmlNodePtr	child;

	child = obj->children;
	while (child)
	{
		if (child->type == XML_ELEMENT_NODE)
		{
			if (ft_strequ((char *)child->name, "pos"))
				sc->lights[i].pos = parse_vec((char *)xmlNodeGetContent(child));
			else if (ft_strequ((char *)child->name, "intensity"))
				sc->lights[i].intensity = ft_atoi((char *)xmlNodeGetContent(child));
			else if (ft_strequ((char *)child->name, "color"))
				sc->lights[i].color = parse_color((char *)xmlNodeGetContent(child));
			else
				ft_err(ft_strjoin("Undefined light argument: ", (char *)child->name), 1);
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