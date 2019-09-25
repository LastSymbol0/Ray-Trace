/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsusol <vsusol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 17:28:37 by aillia            #+#    #+#             */
/*   Updated: 2019/09/05 18:11:11 by vsusol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	*mytime(void *thread)
{
	while (((t_mythread*)thread)->die == 0)
	{
		if (((t_mythread*)thread)->end != 0 && ((t_mythread*)thread)->start != 0)
		{
			printf("The above code block was executed in %.4f second(s)\n", ((double) ((t_mythread*)thread)->end - ((t_mythread*)thread)->start) / ((double) CLOCKS_PER_SEC));
			((t_mythread*)thread)->end = 0;
		}
	}
	return (NULL);
}

int		main(int ac, char **av)
{
	t_scene *sc;

	if (ac == 2)
	{
		sc = parser(av[1]);
		sc->sdl = sdl_init(sc);
		// test_sdl(sc);
		OCL = init_ocl();

		pthread_create(sc->thread.tid, NULL, mytime, &sc->thread);

		sc->thread.start = clock();
			set_ray_arr_ocl(sc);
		sc->thread.end = clock();

		sc->thread.start = clock();
			ray_trace_ocl(sc);
		sc->thread.end = clock();

		sdl_draw(sc);
		hook(sc);
		sdl_destroy(sc);
	}
	else
		write(1, "1 argument plz\n", 15);
	return (0);
}