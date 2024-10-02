/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 21:19:28 by amousaid          #+#    #+#             */
/*   Updated: 2023/11/22 08:40:27 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*p;
	size_t	i;

	if (!s && n == 0)
		return (0);
	p = (char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = (char)c;
		i++;
	}
	return (s);
}
