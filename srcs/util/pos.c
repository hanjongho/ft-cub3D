/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjongho <hanjongho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:26:02 by hanjongho         #+#    #+#             */
/*   Updated: 2021/03/30 20:10:14 by hanjongho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

void	set_pos(t_pos *pos, double x, double y)
{
	pos->x = x;
	pos->y = y;
}

void	copy_pos(t_pos *pos, t_pos *org)
{
	pos->x = org->x;
	pos->y = org->y;
}

double	max(double a, double b)
{
	return (a > b ? a : b);
}
