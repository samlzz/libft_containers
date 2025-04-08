/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:01:38 by sliziard          #+#    #+#             */
/*   Updated: 2025/04/08 14:08:15 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dynbuf.h"

#ifndef LIBFT_H

# include <stdlib.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!n)
		return (dest);
	if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			((uint8_t *)dest)[i] = ((uint8_t *)src)[i];
			i++;
		}
	}
	else
	{
		while (n--)
			((uint8_t *)dest)[n] = ((uint8_t *)src)[n];
	}
	return (dest);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	alloc_s;
	size_t	i;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb >= SIZE_MAX / size)
		return (NULL);
	alloc_s = nmemb * size;
	if (alloc_s > INT32_MAX)
		return (NULL);
	ptr = malloc(alloc_s);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < alloc_s)
		((uint8_t *)ptr)[i++] = 0;
	return (ptr);
}

void	*ft_realloc(void *ptr, size_t og_size, size_t new_size)
{
	void	*new_ptr;

	new_ptr = NULL;
	if (new_size)
	{
		new_ptr = malloc(new_size);
		if (!new_ptr || !ptr)
			return (new_ptr);
		if (new_size < og_size)
			ft_memmove(new_ptr, ptr, new_size);
		else
			ft_memmove(new_ptr, ptr, og_size);
	}
	free(ptr);
	return (new_ptr);
}

#endif
