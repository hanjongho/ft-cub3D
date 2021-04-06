/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjongho <hanjongho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:22:10 by hanjongho         #+#    #+#             */
/*   Updated: 2021/04/05 02:21:14 by hanjongho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "mlx/mlx.h"
# include "../info/info.h"
# include "../util/util.h"

# define KEY_Q			12
# define KEY_W			13
# define KEY_E			14
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define KEY_UP	 		126
# define KEY_DOWN		125
# define KEY_ESC		53
# define KEY_PRESS		2
# define KEY_RELEASE	3
# define KEY_EXIT		17

typedef struct	s_ray
{
	int			column;
	int			row;
	int			direction;
	int			side;
	int			height;
	double		perp_wall_dist;
	double		wall_xy;
	t_pos		ray_pos;
	t_pos		ray_dir;
	t_pos		map_pos;
	t_pos		side_dist;
	t_pos		delta_dist;
	t_pos		step;
}				t_ray;

typedef struct	s_image
{
	int			bpp;
	int			size_line;
	int			endian;
	void		*img;
	void		*ptr;
}				t_image;

typedef struct	s_tex
{
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			endian;
	char		*path;
	void		*tex;
	void		*ptr;
	t_pos		start;
	t_pos		end;
}				t_tex;

typedef struct	s_sprite_draw
{
	int			sprite_screen;
	int			fact;
	int			draw_y_org;
	t_pos		pos;
	t_pos		transform;
	t_pos		spr_s;
	t_pos		draw_x;
	t_pos		draw_y;
	t_pos		tex_pos;
}				t_sprite_draw;

typedef struct	s_sprite
{
	double			distance;
	t_pos			pos;
	t_tex			*tex;
	struct s_sprite	*next;
	struct s_sprite	*sorted;
}				t_sprite;

typedef	struct	s_window
{
	void		*ptr;
	void		*win;
	t_image		screen;
	t_pos		size;
	t_pos		half;
}				t_window;

typedef struct	s_camera
{
	t_pos	pos;
	t_pos	dir;
	t_pos	x_dir;
	t_pos	plane;
}				t_camera;

typedef	struct	s_view
{
	t_info		info;
	t_window	window;
	t_camera	camera;
	t_sprite	*sprites;
	t_tex		tex[TEXTURES];
	t_pos		y_move;
	t_pos		x_move;
	t_pos		rotate;
	double		camera_x[1920];
	double		depth[1920];
	double		sf_dist[1080];
	double		cos[2];
	double		sin[2];
}				t_view;

int				move_camera(t_view *view, int direction, int flag);
int				rotate_camera_x(t_view *view, int direction);
int				free_window(t_window *window);
int				wall_direction(t_ray *ray);
int				map(t_pos p, t_info c);
int				get_tex_pixel(t_tex *tex, t_pos *pos);
int				draw_vertical_line(t_window *window, t_pos *start,
									int length, int color);
void			start_pos(t_info *info, t_camera *camera);
void			start_angle(t_info *info, t_camera *camera);
void			update_view(t_view *view);
void			clear_ui(t_window *window);
void			update_ui(t_view *view);
void			update_window(t_view *view);
void			set_view(t_view *view);
void			destroy_image(t_window *window, t_image *img);
void			draw_pixel(t_window *w, t_pos *pos, int color);
void			draw_sprites(t_view *view);
void			free_sprites(t_sprite **sprites);
void			draw_nswe(t_view *view, t_ray *ray);
void			draw_cf(t_view *view, t_ray *ray);
double			ray_distance(t_view *view, t_ray *ray);
t_sprite		*add_sorted_sprite(t_sprite **sprites, t_sprite *sprite);
t_sprite		*sort_sprites(t_view *view, t_sprite *sprites);
t_sprite		*add_front_sprite(t_sprite **sprites, t_pos *pos, t_tex *tex);

#endif
