/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_file2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 09:35:56 by amousaid          #+#    #+#             */
/*   Updated: 2024/10/05 13:28:43 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	check_first_last_row(char *row)
{
	int	j;

	j = 0;
	while (row[j] != '\n' && row[j] != '\0')
	{
		if (row[j] != '1' && row[j] != ' ')  // Ignore spaces
			return (false);
		j++;
	}
	return (true);
}

// Function to check if the left and right edges of each row are '1's (excluding spaces)
bool	check_edges(char *row)
{
	int	len;

	len = 0;
	while (row[len] != '\n' && row[len] != '\0')
		len++;

	// Ignore spaces on the left and right edges
	int left = 0;
	while (row[left] == ' ')
		left++;
	int right = len - 1;
	while (row[right] == ' ' && right > 0)
		right--;

	// Check if the actual left and right characters are walls ('1')
	if (row[left] != '1' || row[right] != '1')
		return (false);
	return (true);
}

// Check if the map is enclosed by walls
bool	check_map_boundaries(char **map, int i)
{
	int	tmp_i;

	// Skip any leading newline characters
	while (map[i] && map[i][0] == '\n')
		i++;

	// Check first row
	if (!check_first_last_row(map[i]))
		return (false);

	// Check middle rows (left and right edges)
	tmp_i = i + 1;
	while (map[tmp_i] && map[tmp_i + 1] != NULL)  // Ignore the last row
	{
		if (!check_edges(map[tmp_i]))
			return (false);
		tmp_i++;
	}

	// Check last row
	if (!check_first_last_row(map[tmp_i]))
		return (false);

	return (true);
}

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
