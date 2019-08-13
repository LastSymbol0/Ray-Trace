/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 15:06:57 by aillia            #+#    #+#             */
/*   Updated: 2019/08/11 15:10:44 by aillia           ###   ########.fr       */
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
	t_color res;
	int		color;
	int		color_tmp;

	color = abs(ft_atoi_base(s, 16));
	color_tmp = color;
	res.blue = (color_tmp << 24) >> 24;
	color_tmp = color;
	res.green = (color_tmp << 16) >> 24;
	color_tmp = color;
	res.red = (color_tmp << 8) >> 24;
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
		if (cur->type == XML_ELEMENT_NODE && !ft_strequ((char *)cur->name, "light"))
			set_object(sc, cur, i++, get_type((char *)cur->name));
		cur = cur->next;
	}
}

t_scene	*parser(char *filename)
{
	t_scene		*sc;
	xmlDocPtr	doc;
	xmlNodePtr	root;

	printf("Oh shit!\n");
	// sc = NULL;
	sc = (t_scene *)ft_memalloc(sizeof(t_scene));
	doc = xmlReadFile(filename, NULL, 0);
	root = xmlDocGetRootElement(doc);
	scene_memory_alloc(sc, root);
	scene_set_objects(sc, root);
	// sc->objects = (t_obj *)ft_memalloc(sizeof(t_obj) * xmlChildElementCount(root));
	// printf("Root node found!\nName: %s\nAttr0: %s=%s\n\n", root->name, root->properties->name, root->properties->children->content);
	recurs(root, 0);
	return(sc);
}
