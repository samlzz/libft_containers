/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hmap_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:33:10 by sliziard          #+#    #+#             */
/*   Updated: 2025/04/11 14:01:41 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HMAP_INTERNAL_H
# define FT_HMAP_INTERNAL_H

# include "ft_hmap.h"

void	_fill_entry(t_hm_entry *og, t_hmap *map);
int16_t	_hmap_resize(t_hmap *map);

size_t	_get_good_idx(t_hmap *map, const char *key);
bool	_hmap_should_resize(t_hmap map);

#endif
