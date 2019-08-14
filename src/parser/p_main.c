/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsusol <vsusol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 15:06:57 by aillia            #+#    #+#             */
/*   Updated: 2019/08/13 20:02:19 by vsusol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_scene	*parser(char *filename)
{
	t_scene		*sc;
	xmlDocPtr	doc;
	xmlNodePtr	root;

	printf("Oh shit!\n");
	sc = (t_scene *)ft_memalloc(sizeof(t_scene));
	doc = xmlReadFile(filename, NULL, 0);
	root = xmlDocGetRootElement(doc);
	scene_memory_alloc(sc, root);
	if (scene_set_cam(sc, root->children) != 1)
		ft_err("Something wrong with camera count", 1);
	scene_set_objects(sc, root);
	scene_set_lights(sc, root->children);
	// printf("Root node found!\nName: %s\nAttr0: %s=%s\n\n", root->name, root->properties->name, root->properties->children->content);
	recurs(root, 0);
	return(sc);
}
