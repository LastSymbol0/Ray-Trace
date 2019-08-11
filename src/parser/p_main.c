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
		attr = attr->next;
	}
	if (sc->width > 2500 || sc->height > 1500)
		ft_err("Too big window size", 1);
	printf("Name: %s, Width: %d, height: %d\n", sc->name, sc->width, sc->height);
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
	int	obj_count;
	int	light_count;

	light_count = count_lights(root);
	obj_count = xmlChildElementCount(root) - light_count;
	sc = (t_scene *)ft_memalloc(sizeof(t_scene));
	sc->objects = (t_obj *)ft_memalloc(sizeof(t_obj) * obj_count);
	sc->light = (t_light *)ft_memalloc(sizeof(t_light) * light_count);
	set_scene_atr(sc, root);
	sc->ray_arr = (t_ray *)ft_memalloc(sizeof(t_ray) * sc->width * sc->height);
}

t_scene	*parser(char *filename)
{
	t_scene		*sc;
	xmlDocPtr	doc;
	xmlNodePtr	root;

	printf("Oh shit!\n");
	sc = NULL;
	doc = xmlReadFile(filename, NULL, 0);
	root = xmlDocGetRootElement(doc);
	scene_memory_alloc(sc, root);
	// sc->objects = (t_obj *)ft_memalloc(sizeof(t_obj) * xmlChildElementCount(root));
	// printf("Root node found!\nName: %s\nAttr0: %s=%s\n\n", root->name, root->properties->name, root->properties->children->content);
	recurs(root, 0);
	return(0);
}
