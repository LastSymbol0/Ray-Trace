/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 17:28:37 by aillia            #+#    #+#             */
/*   Updated: 2019/08/11 17:28:39 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	set_ray_arr(t_scene *sc)
{
	
}

void	ray_trace(t_scene *sc)
{

}

int		main(int ac, char **av)
{
	t_scene *sc;

	if (ac == 2)
	{
		sc = parser(av[1]);
		set_ray_arr(sc);
		ray_trace(sc);
	}
	else
		write(1, "1 argument plz\n", 15);
	return (0);
}