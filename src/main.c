/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsusol <vsusol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 17:28:37 by aillia            #+#    #+#             */
/*   Updated: 2019/08/13 20:12:56 by vsusol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	set_ray_arr(t_scene *sc)
{
	float	fov;
	int		x;
	int		y;
	float	x1;
	float	y1;

	fov = /*(WIDTH / 960) */ (M_PI / 2);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			x1 = (2 * (x + 0.5) / (float)WIDTH - 1) * tan(fov / 2) *
							(float)WIDTH / (float)HEIGHT;
			y1 = -(2 * (y + 0.5) / (float)HEIGHT - 1) * tan(fov / 2);
			RAY_ARR[x + y * WIDTH].dir = v_norm(v_add(v_new(x1, y1, 0), sc->cam.rot));
			RAY_ARR[x + y * WIDTH].orig = sc->cam.pos;
			x++;
		}
		y++;
	}	
}

// /*
// **	Returns -1 if it's no intersection, and color in any other case
// */
// t_obj	cast_ray(t_scene *sc, t_ray ray, int limit)
// {
// 	int t;
// 	int	i;
// 	t_obj obj;
// 	t_obj tmp;

// 	i = -1;
// 	t = limit;
// 	while (sc->objects[++i])
// 	{
// 		if ((tmp = intersect(sc->objects[i], ray, &t)) != NULL)
// 			obj = tmp;
// 	}
// 	return (t == limit ? NULL : obj);
// }

// void	ray_trace(t_scene *sc)
// {
	// int	x;
	// int	y;

	// y = -1;
	// while(++y < HEIGHT)
	// {
	// 	x = -1;
	// 	while(++x < WIDTH)
	// 	{
	// 		cast_ray(sc, RAY_ARR[x + y * WIDTH], pow(2, 32));
	// 	}
	// }
// }


int		main(int ac, char **av)
{
	t_scene *sc;

	if (ac == 2)
	{
		sc = parser(av[1]);
		sc->sdl = sdl_init(sc);
		test_sdl(sc);


		set_ray_arr(sc);
		// ray_trace(sc);
	}
	else
		write(1, "1 argument plz\n", 15);
	return (0);
}