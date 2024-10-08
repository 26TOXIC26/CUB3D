/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:40:52 by amousaid          #+#    #+#             */
/*   Updated: 2024/10/05 10:25:04 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (fd >= 0 && s)
	{
		i = 0;
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}
// int main()
// {
// 	int fd = open("text.txt",O_CREAT | O_WRONLY,777);
// 	ft_putstr_fd("hello world",fd);
// }
