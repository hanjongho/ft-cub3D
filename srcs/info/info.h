/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjongho <hanjongho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 20:16:22 by hanjongho         #+#    #+#             */
/*   Updated: 2021/04/05 02:38:43 by hanjongho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFO_H
# define INFO_H

# include <math.h>
# include "../libft/libft.h"

# define VALID_MAP "012NSEW"
# define TEXTURES			7
# define N					0
# define S					1
# define W					2
# define E					3
# define SPRITE				4
# define F					5
# define C					6
# define C_R				7
# define C_MAP				8

typedef struct	s_info
{
	int			*map;
	int			width;
	int			height;
	int			rows;
	int			columns;
	int			set[9];
	char		*tex_path[TEXTURES];
	double		rotate_speed;
	double		move_speed;
	double		fov;
	unsigned	c[TEXTURES];
}				t_info;

int				free_info(t_info *info);
void			init_info(t_info *info);
int				parse_info(t_info *info, char const *conf_path);
int				parse_width_height(t_info *info, char const *line);
int				parse_texture(t_info *info, int key, char const *line);
int				parse_rgb(t_info *info, int key, char const *line);
int				parse_map(t_info *info, t_str *map_buffer);

#endif
