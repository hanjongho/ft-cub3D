/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjongho <hanjongho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:40:32 by hanjongho         #+#    #+#             */
/*   Updated: 2021/03/31 19:23:07 by hanjongho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct	s_pos
{
	double	x;
	double	y;
}				t_pos;

typedef struct	s_str
{
	char			*content;
	struct s_str	*next;
}				t_str;

int				ft_atoi(char const *str);
int				ft_endwith(char const *str, char const *end);
int				ft_in_set(char c, char const *set);
t_str			*ft_split(char const *org, char sep);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strdup(const char *s);
char			*ft_strjoin(char *s1, char *s2);
size_t			ft_strlen(const char *str);
char			*ft_substr(char const *str, unsigned int start, size_t len);
int				str_length(t_str *str);
t_str			*str_add_back(t_str **str, char *content);
t_str			*str_last(t_str *str);
int				str_clear(t_str **list);

#endif
