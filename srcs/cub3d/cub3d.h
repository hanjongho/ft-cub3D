/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjongho <hanjongho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:23:00 by hanjongho         #+#    #+#             */
/*   Updated: 2021/04/01 23:38:02 by hanjongho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../raycast/raycast.h"

int				init_window_tex(t_view *view);
int				exit_view(t_view *view);
int				make_bmp(t_view *view);
int				load_texs(t_view *view);
int				parse_texture(t_info *info, int key, char const *line);
int				free_window(t_window *window);
int				init_window(t_window *window, t_info *info);
void			init_view(t_view *view);
void			free_tex(t_view *view);

#endif
