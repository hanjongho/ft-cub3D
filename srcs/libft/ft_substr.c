/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjongho <hanjongho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 22:09:00 by hanjongho         #+#    #+#             */
/*   Updated: 2021/03/24 15:55:24 by hanjongho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t	i;
	char	*str_;

	if (!str)
		return (NULL);
	i = ft_strlen(str);
	if (i < start)
		len = 0;
	else if (i - start < len)
		len = i - start;
	if (!(str_ = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		str_[i] = str[i + start];
		i++;
	}
	str_[i] = 0;
	return (str_);
}
