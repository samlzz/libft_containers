/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:57:42 by sliziard          #+#    #+#             */
/*   Updated: 2025/04/09 14:56:24 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hmap.h"

/**
 * @brief Computes the FNV-1a 64-bit hash of a null-terminated string.
 *
 * @param str The input string to hash (null-terminated).
 * @return uint64_t The resulting 64-bit hash value.
 *
 * @note The hash is calculated as follows:
 *	hash := FNV_offset_basis (64-bit)
 *
 *	for each byte_of_data in input:
 *
 *		- hash := hash XOR byte_of_data
 *
 *		- hash := hash × FNV_prime (mod 2^64)
 */
uint64_t	fnv1a_hash(const char *key)
{
	uint64_t	hash;
	
	hash= FNV_OFFSET_BASIC;
	while (*key)
	{
		hash ^= (uint8_t)(*key++);
		hash *= FNV_PRIME;
	}
	return (hash);
}

bool	hmap_should_resize(t_hmap map)
{
	return ((float)map.count / (float)map.__cap) > HMAP_RESIZE_RATIO;
}
