/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:58:43 by amousaid          #+#    #+#             */
/*   Updated: 2024/10/05 10:29:54 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)s;
	if (!s && !n)
		return (0);
	while (i < n)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (p);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total;

	total = size * count;
	if (total == 0)
	{
		ptr = malloc(1);
		((char *)ptr)[0] = 0;
	}
	else
	{
		if (size && ((total / size) != (count)))
			return (NULL);
		ptr = malloc(total);
		if (ptr == NULL)
			return (NULL);
		ft_bzero(ptr, total);
	}
	return (ptr);
}
