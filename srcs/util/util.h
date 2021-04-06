/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjongho <hanjongho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:23:41 by hanjongho         #+#    #+#             */
/*   Updated: 2021/03/30 20:17:34 by hanjongho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include "../info/info.h"

void			set_pos(t_pos *pos, double x, double y);
void			copy_pos(t_pos *pos, t_pos *org);
int				in_map(t_pos p, t_info c);
int				fint(int x);
int				check_top(t_pos p);
int				check_bot(t_pos p, t_info c);
int				map_xy(int x, int y, t_info c);
double			max(double a, double b);
int				get_map(t_pos p, t_info c);

#endif
