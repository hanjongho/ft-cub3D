/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjongho <hanjongho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:22:17 by hanjongho         #+#    #+#             */
/*   Updated: 2021/04/01 13:47:57 by hanjongho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static void		init_ray(t_ray *r, t_camera *c, int column, double camera_x)
{
	r->column = column;
	set_pos(&r->map_pos, (int)c->pos.x, (int)c->pos.y);
	set_pos(&r->ray_dir,
	c->dir.x + c->plane.x * camera_x, c->dir.y + c->plane.y * camera_x);
	set_pos(&r->delta_dist, fabs(1 / r->ray_dir.x), fabs(1 / r->ray_dir.y));
	if (r->ray_dir.x < 0)
	{
		set_pos(&r->step, -1, (r->ray_dir.y < 0) ? -1 : 1);
		r->side_dist.x = (r->ray_pos.x - r->map_pos.x) * r->delta_dist.x;
	}
	else
	{
		set_pos(&r->step, 1, (r->ray_dir.y < 0) ? -1 : 1);
		r->side_dist.x = (r->map_pos.x + 1 - r->ray_pos.x) * r->delta_dist.x;
	}
	if (r->ray_dir.y < 0)
		r->side_dist.y = (r->ray_pos.y - r->map_pos.y) * r->delta_dist.y;
	else
		r->side_dist.y = (r->map_pos.y + 1 - r->ray_pos.y) * r->delta_dist.y;
}

static void		set_perpwalldist_walldirection(t_view *view, t_ray *ray)
{
	if (ray->side)
	{
		ray->perp_wall_dist = fabs(
			(ray->map_pos.y - view->camera.pos.y + (1 - ray->step.y) / 2)
			/ ray->ray_dir.y);
		ray->direction = (ray->ray_dir.y < 0) ? (N) : (S);
	}
	else
	{
		ray->perp_wall_dist = fabs((ray->map_pos.x - view->camera.pos.x
			+ (1 - ray->step.x) / 2) / ray->ray_dir.x);
		ray->direction = (ray->ray_dir.x < 0) ? (W) : (E);
	}
}

static	void	raycast(t_view *view, t_ray *ray, int column)
{
	int			hit;
	int			next_side;

	copy_pos(&ray->ray_pos, &view->camera.pos);
	init_ray(ray, &view->camera, column, view->camera_x[column]);
	hit = 0;
	while (!hit)
	{
		next_side = (ray->side_dist.x < ray->side_dist.y);
		ray->side_dist.x += (next_side ? ray->delta_dist.x : 0);
		ray->side_dist.y += (!next_side ? ray->delta_dist.y : 0);
		ray->map_pos.x += (next_side ? ray->step.x : 0);
		ray->map_pos.y += (!next_side ? ray->step.y : 0);
		ray->side = !next_side;
		if (!in_map(ray->map_pos, view->info))
		{
			ray->map_pos.x -= (next_side ? ray->step.x : 0);
			ray->map_pos.y -= (!next_side ? ray->step.y : 0);
			hit = 1;
		}
		else if (map(ray->map_pos, view->info) == '1')
			hit = 1;
	}
	set_perpwalldist_walldirection(view, ray);
}

void			update_view(t_view *view)
{
	t_window	*w;
	int			i;
	t_ray		ray;

	w = &view->window;
	i = 0;
	while (i < w->size.x)
	{
		raycast(view, &ray, i);
		view->depth[i] = ray.perp_wall_dist;
		ray.height = fabs(w->size.y / ray.perp_wall_dist);
		draw_nswe(view, &ray);
		if (ray.height < w->size.y)
			draw_cf(view, &ray);
		i++;
	}
	if (view->sprites)
		draw_sprites(view);
}
