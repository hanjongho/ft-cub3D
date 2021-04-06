/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjongho <hanjongho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:40:37 by hanjongho         #+#    #+#             */
/*   Updated: 2021/04/01 13:21:51 by hanjongho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void			set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

static	int			write_bmp_header(int fd, int filesize, t_view *view)
{
	int				i;
	int				tmp;
	unsigned char	bmpfileheader[54];

	i = 0;
	while (i < 54)
		bmpfileheader[i++] = (unsigned char)(0);
	bmpfileheader[0] = (unsigned char)('B');
	bmpfileheader[1] = (unsigned char)('M');
	set_int_in_char(bmpfileheader + 2, filesize);
	bmpfileheader[10] = (unsigned char)(54);
	bmpfileheader[14] = (unsigned char)(40);
	tmp = view->window.size.x;
	set_int_in_char(bmpfileheader + 18, tmp);
	tmp = view->window.size.y;
	set_int_in_char(bmpfileheader + 22, tmp);
	bmpfileheader[27] = (unsigned char)(1);
	bmpfileheader[28] = (unsigned char)(24);
	return (!(write(fd, bmpfileheader, 54) < 0));
}

static int			write_bmp_data(int file, t_window *w, int pad)
{
	char			zero[3];
	int				i;
	int				j;
	int				color;

	i = 0;
	while (i < (int)w->size.y)
	{
		j = 0;
		while (j < (int)w->size.x)
		{
			color = *(int*)(w->screen.ptr
			+ (4 * (int)w->size.x * ((int)w->size.y - 1 - i)) + (4 * j));
			color = (color & 0xFF0000) |
					(color & 0x00FF00) |
					(color & 0x0000FF);
			if (write(file, &color, 3) < 0)
				return (0);
			if (pad > 0 && write(file, &zero, pad) < 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int					save_bmp(t_view *view)
{
	t_window		*w;
	int				filesize;
	int				file;
	int				pad;

	w = &view->window;
	pad = (4 - ((int)w->size.x * 3) % 4) % 4;
	filesize = 54 + (3 * ((int)w->size.x + pad) * (int)w->size.y);
	if ((file = open("capture.bmp", O_WRONLY | O_CREAT |
										O_TRUNC | O_APPEND)) < 0)
		return (0);
	if (!write_bmp_header(file, filesize, view))
		return (0);
	if (!write_bmp_data(file, w, pad))
		return (0);
	close(file);
	return (1);
}

int					make_bmp(t_view *view)
{
	update_view(view);
	mlx_put_image_to_window(view->window.ptr, view->window.win,
							view->window.screen.img, 0, 0);
	if (!save_bmp(view))
		write(1, "Error\n", 5);
	return (exit_view(view));
}
