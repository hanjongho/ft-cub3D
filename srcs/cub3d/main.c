/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjongho <hanjongho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:23:08 by hanjongho         #+#    #+#             */
/*   Updated: 2021/04/05 01:46:15 by hanjongho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		key_press(int keycode, t_view *view)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		view->y_move.x = 1;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		view->y_move.y = 1;
	if (keycode == KEY_A)
		view->x_move.x = 1;
	else if (keycode == KEY_D)
		view->x_move.y = 1;
	if (keycode == KEY_Q || keycode == KEY_LEFT)
		view->rotate.x = 1;
	else if (keycode == KEY_E || keycode == KEY_RIGHT)
		view->rotate.y = 1;
	return (0);
}

static int		key_release(int keycode, t_view *view)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		view->y_move.x = 0;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		view->y_move.y = 0;
	else if (keycode == KEY_A)
		view->x_move.x = 0;
	else if (keycode == KEY_D)
		view->x_move.y = 0;
	else if (keycode == KEY_Q || keycode == KEY_LEFT)
		view->rotate.x = 0;
	else if (keycode == KEY_E || keycode == KEY_RIGHT)
		view->rotate.y = 0;
	else if (keycode == KEY_ESC)
		return (exit_view(view));
	return (0);
}

static int		main_loop(t_view *view)
{
	static int changed = 1;

	if (view->y_move.x || view->y_move.y)
		changed = move_camera(view, (view->y_move.x) ? 0 : 1, 1);
	if (view->x_move.x || view->x_move.y)
		changed = move_camera(view, (view->x_move.x) ? 0 : 1, 0);
	if (view->rotate.x || view->rotate.y)
		changed = rotate_camera_x(view, (view->rotate.x) ? 0 : 1);
	if (changed)
	{
		view->info.map[(fint(view->camera.pos.y)
		* view->info.columns) + fint(view->camera.pos.x)] = 'A';
		update_view(view);
		mlx_put_image_to_window(view->window.ptr, view->window.win,
								view->window.screen.img, 0, 0);
	}
	changed = 0;
	return (0);
}

static	int		input_check(t_info *info)
{
	int i;

	i = -1;
	while (++i < 7)
		if (info->set[i] == 0)
			return (0);
	return (1);
}

int				main(int argc, char **argv)
{
	t_view		view;
	int			c_save;

	c_save = (argc == 3 && !ft_strcmp(argv[1], "--save"));
	init_view(&view);
	if (argc < (2 + c_save)
	|| (argc >= 3 && !c_save)
	|| !parse_info(&view.info, argv[1 + c_save])
	|| !input_check(&view.info)
	|| !init_window_tex(&view))
	{
		write(1, "Error\n", 5);
		return (exit_view(&view));
	}
	if (c_save)
		return (make_bmp(&view));
	mlx_hook(view.window.win, KEY_PRESS, 0, &key_press, &view);
	mlx_hook(view.window.win, KEY_RELEASE, 0, &key_release, &view);
	mlx_hook(view.window.win, KEY_EXIT, 0, &exit_view, &view);
	mlx_loop_hook(view.window.ptr, &main_loop, &view);
	mlx_loop(view.window.ptr);
	return (0);
}
