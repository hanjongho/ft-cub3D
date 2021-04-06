/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjongho <hanjongho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:22:38 by hanjongho         #+#    #+#             */
/*   Updated: 2021/03/30 20:08:21 by hanjongho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	empty_row(t_tex *tex, int row)
{
	int		i;
	t_pos	pos;

	pos.y = row;
	i = -1;
	while (++i < tex->width)
	{
		pos.x = i;
		if (get_tex_pixel(tex, &pos) != 0x0)
			return (0);
	}
	return (1);
}

static int	empty_column(t_tex *tex, int column)
{
	int		i;
	t_pos	pos;

	pos.x = column;
	i = -1;
	while (++i < tex->height)
	{
		pos.y = i;
		if (get_tex_pixel(tex, &pos) != 0x0)
			return (0);
	}
	return (1);
}

static int	load_tex(t_window *window, t_tex *tex, char *path)
{
	if (path)
	{
		tex->path = path;
		if ((tex->tex = mlx_xpm_file_to_image(window->ptr, path, &tex->width,
											&tex->height)))
			tex->ptr = mlx_get_data_addr(tex->tex, &tex->bpp, &tex->size_line,
											&tex->endian);
		else
			return (0);
	}
	return (1);
}

int			load_texs(t_view *view)
{
	int		i;
	int		j;

	i = -1;
	while (++i < TEXTURES)
	{
		if (!load_tex(&view->window, &view->tex[i], view->info.tex_path[i]))
			return (0);
		j = 0;
		while (j < view->tex[i].height && empty_column(&view->tex[i], j))
			j++;
		view->tex[i].start.x = j;
		while (j < view->tex[i].height && !empty_column(&view->tex[i], j))
			j++;
		view->tex[i].end.x = j;
		j = 0;
		while (j < view->tex[i].height && empty_row(&view->tex[i], j))
			j++;
		view->tex[i].start.y = j;
		while (j < view->tex[i].height && !empty_row(&view->tex[i], j))
			j++;
		view->tex[i].end.y = j;
	}
	return (1);
}

void		free_tex(t_view *view)
{
	int		i;

	i = -1;
	while (++i < TEXTURES)
	{
		if (view->tex[i].tex)
			mlx_destroy_image(view->window.ptr, view->tex[i].tex);
		view->tex[i].tex = NULL;
		view->tex[i].ptr = NULL;
	}
}
