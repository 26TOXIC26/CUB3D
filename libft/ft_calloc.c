/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:58:43 by amousaid          #+#    #+#             */
/*   Updated: 2023/11/24 01:01:51 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
