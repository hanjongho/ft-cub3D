/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjongho <hanjongho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 02:51:01 by hanjongho         #+#    #+#             */
/*   Updated: 2021/03/24 15:54:55 by hanjongho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				check_newline(char *backup)
{
	int			i;

	i = -1;
	while (backup[++i])
		if (backup[i] == '\n')
			return (i);
	return (-1);
}

int				split_line(char **backup, char **line, int newline_idx)
{
	char		*temp;

	(*backup)[newline_idx] = '\0';
	*line = ft_strdup(*backup);
	if (!ft_strlen(*backup + newline_idx + 1))
	{
		free(*backup);
		*backup = 0;
		return (1);
	}
	temp = ft_strdup(*backup + newline_idx + 1);
	free(*backup);
	*backup = temp;
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static char	*backup[OPEN_MAX];
	char		buf[BUFFER_SIZE + 1];
	int			read_size;
	int			newline_idx;

	if (fd < 0 || !line || (BUFFER_SIZE <= 0))
		return (-1);
	while ((read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_size] = '\0';
		backup[fd] = ft_strjoin(backup[fd], buf);
		if ((newline_idx = check_newline(backup[fd])) >= 0)
			return (split_line(&backup[fd], line, newline_idx));
	}
	if (read_size < 0)
		return (-1);
	if (backup[fd] && (newline_idx = check_newline(backup[fd])) >= 0)
		return (split_line(&backup[fd], line, newline_idx));
	*line = backup[fd] ? backup[fd] : ft_strdup("");
	if (*line == backup[fd])
		backup[fd] = NULL;
	return (0);
}
