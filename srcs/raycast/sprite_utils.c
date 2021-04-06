/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjongho <hanjongho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:22:28 by hanjongho         #+#    #+#             */
/*   Updated: 2021/03/27 01:19:31 by hanjongho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

t_sprite		*add_front_sprite(t_sprite **sprites, t_pos *pos, t_tex *tex)
{
	t_sprite	*new;

	if (!(new = (t_sprite*)malloc(sizeof(*new))))
		return (NULL);
	copy_pos(&new->pos, pos);
	new->distance = 0;
	new->next = *sprites;
	new->tex = tex;
	*sprites = new;
	return (new);
}

t_sprite		*add_sorted_sprite(t_sprite **sorted, t_sprite *sprite)
{
	t_sprite	*first;
	t_sprite	*previous;

	if (!*sorted)
		return ((*sorted = sprite));
	first = *sorted;
	previous = NULL;
	while (*sorted && sprite->distance < (*sorted)->distance)
	{
		previous = *sorted;
		*sorted = (*sorted)->sorted;
	}
	if (!previous)
	{
		sprite->sorted = *sorted;
		*sorted = sprite;
	}
	else
	{
		sprite->sorted = previous->sorted;
		previous->sorted = sprite;
		*sorted = first;
	}
	return (sprite);
}

t_sprite		*sort_sprites(t_view *view, t_sprite *sprites)
{
	t_sprite	*sorted;
	t_pos		p;

	sorted = NULL;
	copy_pos(&p, &view->camera.pos);
	while (sprites)
	{
		sprites->distance =
		fabs(((p.x - sprites->pos.x) *
		(p.x - sprites->pos.x) + (p.y - sprites->pos.y)
		* (p.y - sprites->pos.y)));
		sprites->sorted = NULL;
		add_sorted_sprite(&sorted, sprites);
		sprites = sprites->next;
	}
	return (sorted);
}

void			free_sprites(t_sprite **sprites)
{
	t_sprite	*tmp;

	while (*sprites)
	{
		tmp = (*sprites)->next;
		free(*sprites);
		*sprites = tmp;
	}
	*sprites = NULL;
}
