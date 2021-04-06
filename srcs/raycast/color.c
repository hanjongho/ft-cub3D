/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjongho <hanjongho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:21:58 by hanjongho         #+#    #+#             */
/*   Updated: 2021/03/30 20:09:12 by hanjongho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

int			get_tex_pixel(t_tex *tex, t_pos *pos)
{
	if (pos->x >= 0 && pos->x < tex->width
	&& pos->y >= 0 && pos->y < tex->height)
	{
		return (*(int*)
		(tex->ptr + (4 * tex->width * (int)pos->y) + (4 * (int)pos->x)));
	}
	return (0);
}

void		draw_pixel(t_window *w, t_pos *pos, int color)
{
	if (pos->x >= 0 && pos->x < w->size.x &&
	pos->y >= 0 && pos->y < w->size.y)
		*(int*)(w->screen.ptr +
		(4 * (int)w->size.x * (int)pos->y) + (4 * (int)pos->x)) = color;
}

int			map(t_pos p, t_info c)
{
	return (c.map[(fint(p.y) * c.columns) + fint(p.x)]);
}
