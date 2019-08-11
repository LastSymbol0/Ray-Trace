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
	set_scene_atr(sc);
	sc->ray_arr = (t_ray *)ft_memalloc(sizeof(t_ray) * sc->width * sc->heigh)
}

t_scene	*parser(char *filename)
{
	t_scene		*sc;
	xmlDocPtr	doc;
	xmlNodePtr	root;

	printf("Oh shit!\n");
	doc = xmlReadFile(filename, NULL, 0);
	root = xmlDocGetRootElement(doc);
	scene_memory_alloc(sc, root);
	// sc->objects = (t_obj *)ft_memalloc(sizeof(t_obj) * xmlChildElementCount(root));
	printf("Root node found!\nName: %s\nAttr0: %s=%s\n\n", root->name, root->properties->name, root->properties->children->content);
	recurs(root, 0);
	return(0);
}
