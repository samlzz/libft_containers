/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:18:34 by sliziard          #+#    #+#             */
/*   Updated: 2025/04/09 16:35:41 by sliziard         ###   ########.fr       */
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
	ft_hmap_iter_full(map, (t_hmd_f)&_destroy_entry, (void *)del);
	free(map->__entries);
	map->__entries = NULL;
	map->count = 0;
	map->__cap = 0;
}

static void	_fill_entry(t_hm_entry *og, t_hmap *map)
{
	size_t	idx;

	idx = fnv1a_hash(og->key) % map->__cap;
	if (map->__entries[idx].val)
	{
		while (map->__entries[idx].val)
		{
			if (!map->__entries[idx].key)
				return ;
			idx = (idx + 1) % map->__cap;
		}
	}
	if (map->__entries[idx].key)
		free(map->__entries[idx].key);
	map->__entries[idx].key = og->key;
	map->__entries[idx].val = og->val;
}

static int16_t	_hmap_resize(t_hmap *map)
{
	t_hmap	new_map;

	if (!hmap_should_resize(*map))
		return (0);
	new_map.__cap = map->__cap * 2;
	if (new_map.__cap < map->__cap || new_map.__cap >= INT64_MAX - 8)
		return (1);
	new_map.__entries = ft_calloc(new_map.__cap, sizeof (t_hm_entry));
	if (!new_map.__entries)
		return (1);
	new_map.count = map->count;
	ft_hmap_iter_full(map, (t_hmd_f)&_fill_entry, &new_map);
	free(map->__entries);
	*map = new_map;
	return (0);
}

static size_t	_get_good_idx(t_hmap *map, const char *key)
{
	size_t	idx;

	idx = fnv1a_hash(key) % map->__cap;
	while (map->__entries[idx].key && ft_strcmp(key, map->__entries[idx].key))
	{
		idx = (idx + 1) % map->__cap;
	}
	return (idx);
}

int16_t	ft_hmap_set(t_hmap *map, const char *key, void *val, \
	void (*del)(void *))
{
	size_t		idx;
	t_hm_entry	new;
	char		*__key;

	idx = _get_good_idx(map, key);
	if (map->__entries[idx].val)
	{
		del(map->__entries[idx].val);
		map->__entries[idx].val = val;
		return (0);
	}
	__key = ft_strdup(key);
	if (!__key)
		return (1);
	map->count++;
	if (_hmap_resize(map))
		return (1);
	new = (t_hm_entry){__key, val};
	_fill_entry(&new, map);
	return (0);
}

void	*ft_hmap_get(t_hmap *map, const char *key)
{
	size_t	idx;

	idx = _get_good_idx(map, key);
	if (!map->__entries[idx].key)
		return (NULL);
	return (map->__entries[idx].val);
}

int16_t	ft_hmap_rm(t_hmap *map, const char *key, void (*del)(void *))
{
	size_t	idx;

	idx = _get_good_idx(map, key);
	if (!map->__entries[idx].key || !map->__entries[idx].val)
		return (1);
	del(map->__entries[idx].val);
	map->__entries[idx].val = NULL;
	return (0);
}
