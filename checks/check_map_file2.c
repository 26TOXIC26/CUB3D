/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_file2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 09:35:56 by amousaid          #+#    #+#             */
/*   Updated: 2024/10/05 15:10:42 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	map_syntax(char **map, int i)
{
	int	j;

	j = 0;
	while (map[i] && map[i][0] == '\n')
		i++;
	if (!map[i])
		return (0);
	while (map[i])
	{
		while (map[i][j] != '\n')
		{
			if (map[i][j] != ' ' && map[i][j] != '1' && map[i][j] != '0'
				&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'W'
				&& map[i][j] != 'E')
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int count_player(char **map, int i)
{
	int count;
	int j;

	count = 0;
	j = 0;
	while (map[i] && map[i][0] == '\n')
		i++;
	while (map[i])
	{
		if (count > 1)
			return (0);
		while (map[i][j] != '\n')
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E')
				count++;
			j++;
		}
		j = 0;
		i++;
	}
	if (count != 1)
		return (0);
	return (1);
}

int	check_map(char **map, int *i)
{
	int	j;

	j = 0;
	if (!map_syntax(map, *i) || !count_player(map, *i) || !check_map_boundaries(map, *i))
		return (ft_error("Error:  Invalid map"), 0);
	return (1);
}
