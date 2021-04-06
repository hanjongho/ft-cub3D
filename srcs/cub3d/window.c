/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjongho <hanjongho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:22:45 by hanjongho         #+#    #+#             */
/*   Updated: 2021/04/05 02:21:05 by hanjongho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				free_window(t_window *window)
{
	if (window->screen.img)
		mlx_destroy_image(window->ptr, window->screen.img);
	if (window->ptr && window->win)
		mlx_destroy_window(window->ptr, window->win);
	return (0);
}

int				init_window(t_window *window, t_info *info)
{
	set_pos(&window->size, info->width, info->height);
	window->size.x = window->size.x > 1920 ? 1920 : window->size.x;
	window->size.x = window->size.x < 640 ? 640 : window->size.x;
	window->size.y = window->size.y > 1080 ? 1080 : window->size.y;
	window->size.y = window->size.y < 360 ? 360 : window->size.y;
	window->ptr = NULL;
	window->win = NULL;
	window->screen.img = NULL;
	if (!(window->ptr = mlx_init())
	|| !(window->win = mlx_new_window(window->ptr, window->size.x,
										window->size.y, "cub3d")))
		return (0);
	set_pos(&window->half, window->size.x / 2, window->size.y / 2);
	if (!(window->screen.img = mlx_new_image(window->ptr, window->size.x,
											window->size.y)))
		return (0);
	window->screen.ptr = mlx_get_data_addr(window->screen.img,
						&window->screen.bpp, &window->screen.size_line,
						&window->screen.endian);
	return (1);
}
