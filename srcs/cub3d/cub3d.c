/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjongho <hanjongho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:23:04 by hanjongho         #+#    #+#             */
/*   Updated: 2021/04/05 01:05:33 by hanjongho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	find_sprites(t_view *view)
{
	int		i;
	int		j;
	t_pos	pos;
	char	c;
	t_tex	*tex;

	view->sprites = NULL;
	i = -1;
	while (++i < view->info.rows)
	{
		j = -1;
		while (++j < view->info.columns)
		{
			set_pos(&pos, j + 0.5, i + 0.5);
			c = map(pos, view->info);
			tex = &view->tex[SPRITE + (c - '0' - 2)];
			if (c >= '2' && c <= '4' && tex->tex
				&& !add_front_sprite(&view->sprites, &pos, tex))
				return (0);
		}
	}
	return (1);
}

int			exit_view(t_view *view)
{
	free_info(&view->info);
	free_window(&view->window);
	free_tex(view);
	free_sprites(&view->sprites);
	exit(0);
}

void		init_view(t_view *view)
{
	int		i;

	i = 0;
	while (i < 9)
		view->tex[i++].tex = NULL;
	init_info(&view->info);
	set_pos(&view->y_move, 0, 0);
	set_pos(&view->x_move, 0, 0);
	set_pos(&view->rotate, 0, 0);
	view->sprites = NULL;
}

int			init_window_tex(t_view *view)
{
	int	i;

	i = -1;
	if (!init_window(&view->window, &view->info))
	{
		write(1, "Error\n", 5);
		return (exit_view(view));
	}
	start_pos(&view->info, &view->camera);
	start_angle(&view->info, &view->camera);
	if (!load_texs(view) || !find_sprites(view))
	{
		write(1, "Error\n", 5);
		return (exit_view(view));
	}
	set_view(view);
	return (1);
}
