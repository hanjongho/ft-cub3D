/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjongho <hanjongho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 20:16:30 by hanjongho         #+#    #+#             */
/*   Updated: 2021/04/05 01:41:57 by hanjongho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "info.h"
#include "../gnl/get_next_line.h"

void			init_info(t_info *info)
{
	int			i;

	i = -1;
	while (++i < TEXTURES)
		info->tex_path[i] = NULL;
	i = -1;
	while (++i < 9)
		info->set[i] = 0;
	info->width = 0;
	info->height = 0;
	info->map = NULL;
	info->rows = 0;
	info->columns = 0;
	info->rotate_speed = .05;
	info->move_speed = .05;
	info->fov = .66;
}

static int		info_dir(char const *line)
{
	if (line[0] == 'R' && line[1] == ' ')
		return (C_R);
	else if (line[0] == 'N' && line[1] == 'O')
		return (N);
	else if (line[0] == 'S' && line[1] == 'O')
		return (S);
	else if (line[0] == 'W' && line[1] == 'E')
		return (W);
	else if (line[0] == 'E' && line[1] == 'A')
		return (E);
	else if (line[0] == 'S' && line[1] == ' ')
		return (SPRITE);
	else if (line[0] == 'F' && line[1] == ' ')
		return (F);
	else if (line[0] == 'C' && line[1] == ' ')
		return (C);
	return (C_MAP);
}

static	int		parse_line(t_info *info, char *line, t_str **map_buffer)
{
	static int	empty_in_map = 0;
	static int	content_after = 0;
	int			length;
	int			dir;

	length = ft_strlen(line);
	if (length == 0 && info->set[C_MAP])
		empty_in_map = 1;
	if (empty_in_map && content_after)
		return (0);
	if (length == 0)
		return (1);
	dir = info_dir(line);
	if (dir != C_MAP && (info->set[dir] || info->set[C_MAP]))
		return (0);
	if (dir == C_R)
		return (parse_width_height(info, line));
	else if (dir >= N && dir <= SPRITE)
		return (parse_texture(info, dir, line));
	else if (dir == F || dir == C)
		return (parse_rgb(info, dir, line));
	info->set[dir] = 1;
	if (empty_in_map)
		content_after = 1;
	return (!!str_add_back(map_buffer, ft_strdup(line)));
}

int				parse_info(t_info *info, char const *conf_path)
{
	int			c_fd;
	char		*line;
	int			r;
	t_str		*map_buffer;

	if (!ft_endwith(conf_path, ".cub"))
		return (0);
	if ((c_fd = open(conf_path, O_RDONLY)) < 0)
		return (0);
	map_buffer = NULL;
	r = 1;
	while (get_next_line(c_fd, &line))
	{
		r = (r && parse_line(info, line, &map_buffer));
		free(line);
	}
	if (r && ft_strlen(line) > 0)
		r = !!str_add_back(&map_buffer, ft_strdup(line));
	free(line);
	close(c_fd);
	if (!r || !parse_map(info, map_buffer))
		return (str_clear(&map_buffer));
	str_clear(&map_buffer);
	return (1);
}

int				free_info(t_info *info)
{
	int			i;

	i = -1;
	while (++i < TEXTURES)
	{
		if (info->tex_path[i])
			free(info->tex_path[i]);
		info->tex_path[i] = NULL;
	}
	if (info->map)
		free(info->map);
	info->map = NULL;
	return (0);
}
