/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atodbl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:10:13 by pc                #+#    #+#             */
/*   Updated: 2024/10/01 12:31:58 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"

// double	d_part(char *s)
// {
// 	double	power;
// 	double	double_part;
// 	int		i;

// 	power = 1;
// 	i = 0;
// 	double_part = 0;
// 	if (s[i] == '.')
// 		i++;
// 	if (s[i] >= 48 && s[i] <= 57)
// 	{
// 		while (s[i])
// 		{
// 			if (s[i] == '+' || s[i] == '-' || s[i] == '.')
// 				is_error();
// 			power /= 10;
// 			double_part = double_part + (s[i++] - 48) * power;
// 		}
// 	}
// 	else
// 		is_error();
// 	return (double_part);
// }

// double	atodbl(char *s)
// {
// 	long	int_part;
// 	int		sign;
// 	int		i;

// 	int_part = 0;
// 	sign = 1;
// 	i = 0;
// 	if (s[i] == '+' || s[i] == '-')
// 	{
// 		if (s[i] == '-')
// 			sign *= -1;
// 		i++;
// 	}
// 	if (!(s[i] >= '0' && s[i] <= '9'))
// 		is_error();
// 	while (s[i] != '.' && s[i])
// 	{
// 		if (s[i] == '+' || s[i] == '-')
// 			is_error();
// 		int_part = (int_part * 10) + (s[i++] - 48);
// 	}
// 	if (s[i] == '.')
// 		return ((int_part + d_part(&s[i])) * sign);
// 	else
// 		return (int_part * sign);
// }
