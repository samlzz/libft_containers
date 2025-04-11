/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:18:34 by sliziard          #+#    #+#             */
/*   Updated: 2025/04/11 14:06:25 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hmap.h"
#include <stdlib.h>

t_hmap	ft_hmap_new(size_t *init_cap)
{
	t_hmap	new;

	new.count = 0;
	if (init_cap)
		new.__cap = *init_cap;
	else
		new.__cap = HMAP_INIT_CAP;
	new.__entries = ft_calloc(new.__cap, sizeof (t_hm_entry));
	if (!new.__entries)
		new.__cap = 0;
	return (new);
}

static void	_destroy_entry(t_hm_entry *elem, void (*del)(void *))
{
	if (elem->val)
		del(elem->val);
	free(elem->key);
}

void	ft_hmap_free(t_hmap *map, void (*del)(void *))
{
	ft_hmap_iter_full(map, (t_hmd_f)_destroy_entry, (void *)del);
	free(map->__entries);
	map->__entries = NULL;
	map->count = 0;
	map->__cap = 0;
}
