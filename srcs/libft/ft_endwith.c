/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endwith.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjongho <hanjongho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:25:26 by hanjongho         #+#    #+#             */
/*   Updated: 2021/03/26 00:16:39 by hanjongho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	ft_endwith(char const *str, char const *end)
{
	size_t	len;
	size_t	end_len;

	len = ft_strlen(str);
	end_len = ft_strlen(end);
	if (end_len > len)
		return (0);
	return (!ft_strcmp(str + len - end_len, end));
}
