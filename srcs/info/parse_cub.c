/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjongho <hanjongho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:21:25 by hanjongho         #+#    #+#             */
/*   Updated: 2021/04/05 01:26:47 by hanjongho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "info.h"

static char		*get_path(int start, char const *line)
{
	int			start_def;
	int			end;
	char		*path;

	start_def = start;
	if (!line)
		return (NULL);
	while (line[start] == ' ')
		start++;
	end = ft_strlen(line);
	while (line[end - 1] == ' ')
		end--;
	if (start == start_def || end - start <= 0
		|| !(path = ft_substr(line, start, end - start)))
		return (NULL);
	return (path);
}

static int		calc_rgb(t_str *str)
{
	int			i;
	int			color;
	int			tmp;

	i = 0;
	color = 0;
	while (str)
	{
		tmp = ft_atoi(str->content);
		if (tmp < 0 || tmp > 255)
			return (-1);
		color |= (tmp << (16 - (i++ * 8)));
		str = str->next;
	}
	return (color);
}

int				parse_width_height(t_info *info, char const *line)
{
	int			i;
	int			tmp;
	t_str		*str;
	t_str		*param;

	i = 0;
	while (line[++i])
		if (line[i] != ' ' && line[i] < '0' && line[i] > '9')
			return (0);
	str = NULL;
	if (!(str = ft_split(line, ' ')) || str_length(str) != 3)
		return (str_clear(&str));
	param = str->next;
	tmp = ft_atoi(param->content);
	if (tmp <= 1)
		return (str_clear(&str));
	info->width = tmp;
	param = param->next;
	tmp = ft_atoi(param->content);
	if (tmp <= 1)
		return (str_clear(&str));
	info->height = tmp;
	return (str_clear(&str) | 1);
}

int				parse_rgb(t_info *info, int key, char const *line)
{
	int			i;
	unsigned	color;
	t_str		*str[2];

	i = 1;
	while (line[i])
		if (!ft_in_set(line[i++], " ,0123456789"))
			return (0);
	str[0] = NULL;
	str[1] = NULL;
	if (!(str[0] = ft_split(line, ' ')) || str_length(str[0]) != 2
		|| !(str[1] = ft_split(str[0]->next->content, ','))
		|| str_length(str[1]) != 3)
		return (str_clear(&str[0]) || str_clear(&str[1]));
	if ((int)((color = calc_rgb(str[1]))) < 0)
		return (str_clear(&str[0]) || str_clear(&str[1]));
	info->c[key] = color;
	info->set[key] = 1;
	return ((str_clear(&str[0]) || str_clear(&str[1])) | 1);
}

int				parse_texture(t_info *info, int key, char const *line)
{
	char		*path;

	if (info->tex_path[key])
	{
		free(info->tex_path[key]);
		info->tex_path[key] = NULL;
	}
	if (!(path = get_path((key == SPRITE) ? 1 : 2, line)))
		return (0);
	info->tex_path[key] = path;
	info->set[key] = 1;
	return (1);
}
