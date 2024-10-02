/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 22:55:22 by amousaid          #+#    #+#             */
/*   Updated: 2023/11/22 08:55:37 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_size(long n)
{
	size_t	sum;

	sum = 0;
	if (n <= 0)
	{
		sum++;
		n = n * -1;
	}
	while (n > 0)
	{
		n = n / 10;
		sum++;
	}
	return (sum);
}

static char	*is_positive(long nb, size_t size, char *str)
{
	if (nb < 0)
	{
		str[0] = '-';
		nb = nb * -1;
	}
	while (nb > 0)
	{
		str[size--] = (nb % 10) + 48;
		nb = nb / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	size;
	long	nb;

	nb = n;
	size = ft_size(nb);
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[size--] = '\0';
	if (nb == 0)
	{
		str[0] = '0';
		return (str);
	}
	str = is_positive(nb, size, str);
	return (str);
}
