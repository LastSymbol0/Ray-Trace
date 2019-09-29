/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_screenshot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 14:57:57 by aillia            #+#    #+#             */
/*   Updated: 2019/09/29 14:57:58 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static char	*ft_strjoin_upd(char *s1, char const *s2)
{
	char	*r;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	r = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (r == NULL)
		return (NULL);
	while (s1[j] != '\0')
		r[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		r[i++] = s2[j++];
	r[i] = '\0';
	free(s1);
	s1 = NULL;
	return (r);
}

static char	*ft_name_create(char *pre)
{
	int		i;
	char	*name;
	char	*time_s;
	time_t	cur_time;

	cur_time = time(NULL);
	time_s = ctime(&cur_time);
	name = ft_strnew(ft_strlen(time_s) + 16);
	i = -1;
	while (++i < 11)
		name[i] = pre[i];
	while (time_s[i])
	{
		name[i] = time_s[i];
		i++;
	}
	return (ft_strjoin_upd(name, ".bmp"));
}

void		save_screeshot_bmp_h(t_scene *sc, SDL_Surface *save_surface,
						SDL_Surface *info_surface, unsigned char *pixels)
{
	if (SDL_RenderReadPixels(sc->sdl->render, &info_surface->clip_rect,
	info_surface->format->format, pixels, info_surface->w *
	info_surface->format->BytesPerPixel) != 0)
	{
		free(pixels);
		ft_err("err screenshot2", 1);
	}
	else
	{
		save_surface = SDL_CreateRGBSurfaceFrom(pixels, info_surface->w,
		info_surface->h, info_surface->format->BitsPerPixel,
		info_surface->w * info_surface->format->BytesPerPixel,
		info_surface->format->Rmask, info_surface->format->Gmask,
		info_surface->format->Bmask, info_surface->format->Amask);
		if (save_surface == NULL)
			ft_err("err screenshot3", 1);
		SDL_SaveBMP(save_surface, "RT_screen.bmp");
		SDL_FreeSurface(save_surface);
	}
}

void		save_screenshot_bmp(t_scene *sc)
{
	SDL_Surface		*save_surface;
	SDL_Surface		*info_surface;
	unsigned char	*pixels;

	save_surface = NULL;
	info_surface = NULL;
	if (!(info_surface = SDL_GetWindowSurface(sc->sdl->window)))
		ft_err("err screenshot", 1);
	else
	{
		pixels = (unsigned char *)ft_memalloc(info_surface->w *
						info_surface->h * info_surface->format->BytesPerPixel);
		if (pixels == 0)
			ft_err("err screenshot1", 1);
		else
		{
			save_screeshot_bmp_h(sc, save_surface, info_surface, pixels);
			free(pixels);
		}
		SDL_FreeSurface(info_surface);
	}
}
