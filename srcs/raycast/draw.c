/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjongho <hanjongho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:22:01 by hanjongho         #+#    #+#             */
/*   Updated: 2021/04/01 12:05:45 by hanjongho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static void	init_draw_wall(t_tex *tex, t_ray *ray, t_pos *p_tex)
{
	ray->wall_xy = ray->side ?
	ray->ray_pos.x +
	((ray->map_pos.y - ray->ray_pos.y + (1 - ray->step.y) / 2)
	/ ray->ray_dir.y) * ray->ray_dir.x
	:
	ray->ray_pos.y +
	((ray->map_pos.x - ray->ray_pos.x + (1 - ray->step.x) / 2)
	/ ray->ray_dir.x) * ray->ray_dir.y;
	ray->wall_xy -= floor(ray->wall_xy);
	p_tex->x = (int)(ray->wall_xy * tex->width);
	if ((!ray->side && ray->ray_dir.x > 0)
	|| (ray->side && ray->ray_dir.y < 0))
		p_tex->x = tex->width - p_tex->x - 1;
}

static int	draw_default_color(t_window *window, t_pos *start,
										int length, int color)
{
	int		i;
	int		j;
	t_pos	pos;
	int		limit;

	if (0 <= start->x && start->x <= window->size.x)
	{
		pos.x = start->x;
		limit = (int)window->size.y;
		i = 0;
		while (i < length && (j = start->y + i) < limit)
		{
			pos.y = j;
			draw_pixel(window, &pos, color);
			i++;
		}
	}
	return (1);
}

void		draw_cf(t_view *view, t_ray *ray)
{
	int		i;
	t_pos	pixel;

	pixel.x = ray->column;
	i = view->window.half.y + (ray->height / 2);
	while (i < view->window.size.y)
	{
		pixel.y = i;
		draw_pixel(&view->window, &pixel, view->info.c[F]);
		pixel.y = view->window.size.y - i++;
		draw_pixel(&view->window, &pixel, view->info.c[C]);
	}
}

void		draw_nswe(t_view *g, t_ray *ray)
{
	int		i;
	int		j;
	t_pos	p_tex;
	t_tex	*tex;
	t_pos	pixel;

	tex = &g->tex[ray->direction];
	set_pos(&pixel, ray->column,
					max(0, g->window.half.y - (ray->height / 2.0)));
	if (!tex->tex)
		draw_default_color(&g->window, &pixel,
							ray->height, g->info.c[ray->direction]);
	else
	{
		init_draw_wall(tex, ray, &p_tex);
		i = -1;
		j = pixel.y;
		while (++i < ray->height && (pixel.y = j++) < g->window.size.y)
		{
			p_tex.y = (int)((pixel.y * 2 - g->window.size.y + ray->height)
			* ((tex->height / 2.0) / ray->height));
			draw_pixel(&g->window, &pixel, get_tex_pixel(tex, &p_tex));
		}
	}
}
