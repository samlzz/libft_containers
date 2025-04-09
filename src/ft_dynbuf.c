/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynbuf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 22:13:41 by sliziard          #+#    #+#             */
/*   Updated: 2025/04/09 13:17:52 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dynbuf.h"
#include <stdlib.h>

t_dynbuf	ft_dynbuf_new(size_t *init_cap)
{
	t_dynbuf	buf;

	if (init_cap)
		buf.capacity = *init_cap;
	else
		buf.capacity = DYNBUF_INIT_CAP;
	buf.data = ft_calloc(buf.capacity + 1, sizeof (char));
	if (!buf.data)
	{
		buf.capacity = 0;
		buf.len = 0;
		return (buf);
	}
	buf.len = 0;
	return (buf);
}

static int16_t	_dynbuf_resize(t_dynbuf *buf, size_t min_cap)
{
	size_t	new_cap;
	char	*new_data;

	new_cap = buf->capacity * DYNBUF_REALOC_FACTOR;
	while (new_cap < min_cap)
		new_cap *= DYNBUF_REALOC_FACTOR;
	new_data = ft_realloc(buf->data, buf->len, new_cap);
	if (!new_data)
		return (0);
	new_data[buf->len] = '\0';
	buf->data = new_data;
	buf->capacity = new_cap;
	return (1);
}

char	*ft_dynbuf_append_char(t_dynbuf *buf, char c)
{
	if (buf->len + 1 >= buf->capacity)
		if (!_dynbuf_resize(buf, buf->len + 1))
			return (NULL);
	buf->data[buf->len++] = c;
	buf->data[buf->len] = '\0';
	return (buf->data);
}

char	*ft_dynbuf_append_str(t_dynbuf *buf, const char *s)
{
	size_t	slen;

	if (!s)
		return (buf->data);
	slen = ft_strlen(s);
	if (buf->len + slen >= buf->capacity)
		if (!_dynbuf_resize(buf, buf->len + slen))
			return (NULL);
	ft_memmove(buf->data + buf->len, s, slen);
	buf->len += slen;
	buf->data[buf->len] = '\0';
	return (buf->data);
}

void	ft_dynbuf_free(t_dynbuf *buf)
{
	free(buf->data);
	buf->data = NULL;
	buf->len = 0;
	buf->capacity = 0;
}
