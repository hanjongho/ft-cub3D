/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjongho <hanjongho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 19:23:40 by hanjongho         #+#    #+#             */
/*   Updated: 2021/03/30 20:10:08 by hanjongho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

int		in_map(t_pos p, t_info c)
{
	return (check_top(p) && check_bot(p, c));
}

int		fint(int x)
{
	return (int)floor(x);
}

int		check_top(t_pos p)
{
	return (fint(p.x) >= 0 && fint(p.y) >= 0);
}

int		check_bot(t_pos p, t_info c)
{
	return (fint(p.x) < c.columns && fint(p.y) < c.rows);
}

int		map_xy(int x, int y, t_info c)
{
	return (c.map[(fint(y) * c.columns) + fint(x)]);
}
