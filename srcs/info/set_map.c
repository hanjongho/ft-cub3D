/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjongho <hanjongho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:21:21 by hanjongho         #+#    #+#             */
/*   Updated: 2021/04/05 03:19:12 by hanjongho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "info.h"

static int	len_row_col(t_info *info, t_str *map_buffer)
{
	int		i;
	int		j;
	int		ret;

	ret = -1;
	j = 0;
	if (!map_buffer)
		return (0);
	while (map_buffer)
	{
		i = 0;
		while (map_buffer->content[i])
			i++;
		if (i > ret)
			ret = i;
		map_buffer = map_buffer->next;
		j++;
	}
	info->columns = ret + 1;
	info->rows = j;
	return (1);
}

static	int	copy_map(t_info *info, t_str *map_buffer, int *map)
{
	int		i;
	int		j;
	int		start_check;
	int		line;
	int		has_camera;

	i = 0;
	has_camera = 0;
	while (map_buffer)
	{
		j = -1;
		line = -1;
		start_check = 0;
		while (map_buffer->content[++j])
		{
			map[(i * info->columns) + (++line)] = map_buffer->content[j];
			if (ft_in_set(map_buffer->content[j], "NSWE"))
				has_camera++;
		}
		map[(i * info->columns) + (++line)] = ' ';
		map_buffer = map_buffer->next;
		i++;
	}
	return (has_camera);
}

static int	check_wall(t_info *info, int *map)
{
	int		i;
	int		j;
	int		tmp;

	tmp = -1;
	while (++tmp < info->rows)
	{
		j = -1;
		while (++j < info->columns)
		{
			i = tmp * info->columns;
			if (map[i + j] == '0' || map[i + j] == '2'
			|| map[i + j] == 'N' || map[i + j] == 'S'
			|| map[i + j] == 'E' || map[i + j] == 'W')
			{
				if (!ft_in_set(map[i + j - info->columns], VALID_MAP)
				|| !ft_in_set(map[i + j + info->columns], VALID_MAP)
				|| !ft_in_set(map[i + j - 1], VALID_MAP)
				|| !ft_in_set(map[i + j + 1], VALID_MAP))
					return (0);
			}
		}
	}
	return (1);
}

int			parse_map(t_info *info, t_str *map_buffer)
{
	int		*map;

	map = NULL;
	if (!len_row_col(info, map_buffer)
		|| !(map = (int*)malloc(sizeof(int) * (info->rows * info->columns)))
		|| copy_map(info, map_buffer, map) != 1
		|| !check_wall(info, map)
		|| info->columns <= 2 || info->rows <= 2)
		return (0);
	info->map = map;
	return (1);
}
