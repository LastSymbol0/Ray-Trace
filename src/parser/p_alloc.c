/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_alloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsusol <vsusol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 16:50:27 by aillia            #+#    #+#             */
/*   Updated: 2019/08/13 19:35:36 by vsusol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	set_scene_atr(t_scene *sc, xmlNodePtr root)
{
	xmlAttrPtr attr;

	sc->name = "RT";
	sc->width = 1024;
	sc->height = 720;
	attr = root->properties;
	while (attr)
	{
		if (ft_strequ((char *)attr->name, "name"))
			sc->name = (char *)attr->children->content;
		else if (ft_strequ((char *)attr->name, "width"))
			sc->width = ft_atoi((char *)attr->children->content);
		else if (ft_strequ((char *)attr->name, "height"))
			sc->height = ft_atoi((char *)attr->children->content);
		else if (ft_strequ((char *)attr->name, "ambient"))
			sc->ambient = ft_atoi((char *)attr->children->content);
		else if (ft_strequ((char *)attr->name, "max_reflections"))
			sc->max_reflections = ft_atoi((char *)attr->children->content);
		attr = attr->next;
	}
	if (sc->width > 2500 || sc->height > 1500)
		ft_err("Too big window size", 1);
	printf("Name: %s, Width: %d, height: %d, max_reflections: %d, ambient: %f\n", sc->name, sc->width, sc->height, sc->max_reflections, sc->ambient);
}

int		count_lights(xmlNodePtr cur)
{
	int	n;

	n = 0;
	while (cur)
	{
		if (cur->type == XML_ELEMENT_NODE && ft_strequ((char *)cur->name, "light"))
			n++;
		cur = cur->next;
	}
	return (n);
}

void	scene_memory_alloc(t_scene *sc, xmlNodePtr root)
{
	sc->light_count = count_lights(root->children);
	sc->obj_count = xmlChildElementCount(root) - sc->light_count;
	if (sc->obj_count > MAX_OBJ_COUNT)
		ft_err("Too much objects", 1);	
	// sc = (t_scene *)ft_memalloc(sizeof(t_scene));
	sc->objects = (t_obj *)ft_memalloc(sizeof(t_obj) * (sc->obj_count));
	sc->lights = (t_light *)ft_memalloc(sizeof(t_light) * (sc->light_count + 1));
	set_scene_atr(sc, root);
	sc->ray_arr = (t_ray *)ft_memalloc(sizeof(t_ray) * sc->width * sc->height);
}
