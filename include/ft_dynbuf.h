/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynbuf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliziard <sliziard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:47:18 by sliziard          #+#    #+#             */
/*   Updated: 2025/04/09 12:07:39 by sliziard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DYNBUF_H
# define FT_DYNBUF_H

# include "libft.h"

# ifndef DYNBUF_INIT_CAP
#  define DYNBUF_INIT_CAP		8
# endif
# ifndef DYNBUF_REALOC_FACTOR
#  define DYNBUF_REALOC_FACTOR	2
# endif

typedef struct s_dynbuf
{
	char	*data;
	size_t	len;
	size_t	capacity;
}	t_dynbuf;

t_dynbuf	ft_dynbuf_new(int32_t *init_cap);

char		*ft_dynbuf_append_str(t_dynbuf *buf, const char *s)
			__attribute__ ((nonnull(1)));

char		*ft_dynbuf_append_char(t_dynbuf *buf, char c)
			__attribute__ ((nonnull(1)));

void		ft_dynbuf_free(t_dynbuf *buf)
			__attribute__ ((nonnull(1)));

#endif
