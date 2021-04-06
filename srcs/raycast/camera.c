/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjongho <hanjongho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:21:34 by hanjongho         #+#    #+#             */
/*   Updated: 2021/04/01 12:59:24 by hanjongho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void			start_pos(t_info *info, t_camera *camera)
{
	camera->pos.y = -1;
	while (++camera->pos.y < info->rows)
	{
		camera->pos.x = -1;
		while (++camera->pos.x < info->columns)
		{
			if (ft_in_set(map(camera->pos, *info), "NSEW"))
			{
				camera->pos.x += 0.5;
				camera->pos.y += 0.5;
				return ;
			}
		}
	}
}

void			start_angle(t_info *info, t_camera *camera)
{
	if (map(camera->pos, *info) == 'N')
	{
		set_pos(&camera->dir, 0, -1);
		set_pos(&camera->plane, info->fov, 0);
	}
	else if (map(camera->pos, *info) == 'E')
	{
		set_pos(&camera->dir, 1, 0);
		set_pos(&camera->plane, 0, info->fov);
	}
	else if (map(camera->pos, *info) == 'S')
	{
		set_pos(&camera->dir, 0, 1);
		set_pos(&camera->plane, -info->fov, 0);
	}
	else if (map(camera->pos, *info) == 'W')
	{
		set_pos(&camera->dir, -1, 0);
		set_pos(&camera->plane, 0, -info->fov);
	}
	set_pos(&camera->x_dir, camera->dir.y, -camera->dir.x);
}

int				move_camera(t_view *view, int direction, int flag)
{
	t_camera	*c;
	t_pos		next_pos;
	double		tmp_x;
	double		tmp_y;

	c = &view->camera;
	tmp_x = flag ? c->dir.x : c->x_dir.x;
	tmp_y = flag ? c->dir.y : c->x_dir.y;
	copy_pos(&next_pos, &c->pos);
	next_pos.x += ((direction ? -1 : 1) * (tmp_x * .11));
	if (in_map(next_pos, view->info)
		&& map(next_pos, view->info) != '1')
		copy_pos(&c->pos, &next_pos);
	copy_pos(&next_pos, &c->pos);
	next_pos.y += ((direction ? -1 : 1) * (tmp_y * .11));
	if (in_map(next_pos, view->info)
		&& map(next_pos, view->info) != '1')
		copy_pos(&c->pos, &next_pos);
	return (1);
}

int				rotate_camera_x(t_view *view, int dir)
{
	t_camera	*c;
	double		tmp_x;

	c = &view->camera;
	tmp_x = c->dir.x;
	c->dir.x = (c->dir.x * view->cos[dir]) - (c->dir.y * view->sin[dir]);
	c->dir.y = (tmp_x * view->sin[dir]) + (c->dir.y * view->cos[dir]);
	tmp_x = c->plane.x;
	c->plane.x = (c->plane.x * view->cos[dir]) - (c->plane.y * view->sin[dir]);
	c->plane.y = (tmp_x * view->sin[dir]) + (c->plane.y * view->cos[dir]);
	tmp_x = c->x_dir.x;
	c->x_dir.x = (c->x_dir.x * view->cos[dir]) - (c->x_dir.y * view->sin[dir]);
	c->x_dir.y = (tmp_x * view->sin[dir]) + (c->x_dir.y * view->cos[dir]);
	return (1);
}

void			set_view(t_view *view)
{
	int			i;

	i = -1;
	while (++i < view->window.size.x)
		view->camera_x[i] = ((2 * (double)i) / view->window.size.x) - 1;
	view->cos[0] = cos(-view->info.rotate_speed);
	view->cos[1] = cos(view->info.rotate_speed);
	view->sin[0] = sin(-view->info.rotate_speed);
	view->sin[1] = sin(view->info.rotate_speed);
}
