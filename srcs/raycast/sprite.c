/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjongho <hanjongho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:22:32 by hanjongho         #+#    #+#             */
/*   Updated: 2021/03/27 02:01:30 by hanjongho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static void			init_draw_sprite(t_view *view, t_sprite *sprite,
									double inv_det, t_sprite_draw *spr)
{
	spr->pos.x = sprite->pos.x - view->camera.pos.x;
	spr->pos.y = sprite->pos.y - view->camera.pos.y;
	spr->transform.x = inv_det *
	(view->camera.dir.y * spr->pos.x - view->camera.dir.x * spr->pos.y);
	spr->transform.y = inv_det *
	(-view->camera.plane.y * spr->pos.x + view->camera.plane.x * spr->pos.y);
	spr->sprite_screen = (int)((view->window.size.x / 2.)
	* (1. + spr->transform.x / spr->transform.y));
	spr->spr_s.x = fabs(view->window.size.y / spr->transform.y);
	spr->spr_s.y = fabs(view->window.size.y / spr->transform.y);
	spr->draw_x.x = (max(0, -spr->spr_s.x / 2. + spr->sprite_screen));
	spr->draw_x.y = (max(0, spr->spr_s.x / 2. + spr->sprite_screen));
	spr->draw_y.x = (max(0, -spr->spr_s.y / 2. + view->window.size.y / 2.));
	spr->draw_y.y = (max(0, spr->spr_s.y / 2. + view->window.size.y / 2.));
	spr->draw_y_org = spr->draw_y.x;
}

static int			set_tex_pos(t_view *view, t_sprite_draw *spr,
								t_tex *tex, t_pos *tex_pos)
{
	tex_pos->x = (int)(256 *
	(((int)(spr->draw_x.x) - (-spr->spr_s.x / 2. + spr->sprite_screen)))
	* tex->width / spr->spr_s.x) / 256;
	if (tex_pos->x < tex->start.x || tex_pos->x > tex->end.x)
		return (0);
	spr->fact = ((int)(spr->draw_y.x) * 256.) - (view->window.size.y * 128.)
				+ (spr->spr_s.y * 128.);
	tex_pos->y = ((spr->fact * tex->height) / spr->spr_s.y) / 256.;
	return (tex_pos->y > tex->start.y && tex_pos->y < tex->end.y);
}

static void			draw_sprite_pixel(t_view *view, t_sprite_draw *spr,
										t_tex *tex)
{
	t_pos			pixel;
	t_pos			tex_pos;
	int				color;

	set_pos(&pixel, spr->draw_x.x, spr->draw_y.x);
	if (set_tex_pos(view, spr, tex, &tex_pos))
	{
		color = get_tex_pixel(tex, &tex_pos);
		if (color != 0x0)
			draw_pixel(&view->window, &pixel, color);
	}
}

static void			draw_sprite(t_view *view, t_sprite *sprite,
								t_sprite_draw *spr, t_tex *tex)
{
	t_sprite		*tmp;

	tmp = sprite;
	while (spr->draw_x.x < view->window.size.x && spr->draw_x.x < spr->draw_x.y)
	{
		if (spr->transform.y > 0.0
		&& spr->transform.y < view->depth[(int)spr->draw_x.x])
		{
			spr->draw_y.x = spr->draw_y_org;
			while (spr->draw_y.x < view->window.size.y
			&& spr->draw_y.x < spr->draw_y.y)
			{
				draw_sprite_pixel(view, spr, tex);
				spr->draw_y.x++;
			}
		}
		spr->draw_x.x++;
	}
}

void				draw_sprites(t_view *view)
{
	t_sprite		*sorted;
	double			inv_det;
	t_sprite_draw	spr;

	inv_det = 1.0 / ((view->camera.plane.x * view->camera.dir.y)
	- (view->camera.plane.y * view->camera.dir.x));
	sorted = sort_sprites(view, view->sprites);
	while (sorted)
	{
		if (sorted->distance > 0.1)
		{
			init_draw_sprite(view, sorted, inv_det, &spr);
			draw_sprite(view, sorted, &spr, sorted->tex);
		}
		sorted = sorted->sorted;
	}
}
