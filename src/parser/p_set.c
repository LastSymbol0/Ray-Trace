/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_set.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsusol <vsusol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 19:55:38 by aillia            #+#    #+#             */
/*   Updated: 2019/08/13 20:05:41 by vsusol           ###   ########.fr       */
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
				sc->objects[i].rot = parse_vec((char *)xmlNodeGetContent(child));
			else if (ft_strequ((char *)child->name, "radius"))
				sc->objects[i].radius = ft_atoi((char *)xmlNodeGetContent(child));
			else if (ft_strequ((char *)child->name, "color"))
				sc->objects[i].color = parse_color((char *)xmlNodeGetContent(child));
		}
		child = child->next;
	}
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

// void	scene_set_light(t_scene *sc, xmlNodePtr cur)
// {

// }