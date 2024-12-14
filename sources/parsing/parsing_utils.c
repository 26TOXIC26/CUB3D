/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 09:19:46 by amousaid          #+#    #+#             */
/*   Updated: 2024/12/12 23:57:38 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_a_white_space(char c)
{
	if (c != ' ' && c != '\t' && c != '\r' && c != '\n' && c != '\v'
		&& c != '\f')
		return (FAILURE);
	else
		return (SUCCESS);
}

size_t	find_biggest_len(t_mapinfo *map, int i)
{
	size_t	biggest_len;

	biggest_len = ft_strlen(map->file[i]);
	while (map->file[i])
	{
		if (ft_strlen(map->file[i]) > biggest_len)
			biggest_len = ft_strlen(map->file[i]);
		i++;
	}
	return (biggest_len);
}

int	is_nsew(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	check_around_zero(char **map_tab)
{
	int	i;
	int	j;

	i = 0;
	while (map_tab[i])
	{
		j = 0;
		while (map_tab[i][j])
		{
			if (map_tab[i][j] == '0')
			{
				if (ft_strlen(map_tab[i - 1]) < (size_t)j || ft_strlen(map_tab[i
							+ 1]) < (size_t)j || is_a_white_space(map_tab[i][j
						- 1]) == SUCCESS || is_a_white_space(map_tab[i][j
						+ 1]) == SUCCESS || is_a_white_space(map_tab[i
						- 1][j]) == SUCCESS || is_a_white_space(map_tab[i
						+ 1][j]) == SUCCESS)
					return (FAILURE);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
