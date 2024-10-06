/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_file2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 09:35:56 by amousaid          #+#    #+#             */
/*   Updated: 2024/10/06 15:41:20 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"



static void	ft_reset_visited(char **visited)
{
	int	i;
	int	j;

	i = 0;
	while (visited[i])
	{
		j = 0;
		while (visited[i][j])
		{
			visited[i][j] = '0';
			j++;
		}
		i++;
	}
}

static int	ft_get_map_dims(char **map, int *height, int *max_len)
{
	int	i;
	int	j;

	i = 0;
	*max_len = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > *max_len)
			*max_len = j;
		i++;
	}
	*height = i;
	return (1);
}

static char	**ft_alloc_visited(int height, int max_len)
{
	char	**visited;
	int		i;

	visited = (char **)malloc(sizeof(char *) * (height + 1));
	if (!visited)
		return (NULL);
	visited[height] = NULL;
	i = 0;
	while (i < height)
	{
		visited[i] = (char *)malloc(max_len + 1);
		if (!visited[i])
		{
			free_tab(visited);
			return (NULL);
		}
		ft_memset(visited[i], '0', max_len);
		visited[i][max_len] = '\0';
		i++;
	}
	return (visited);
}

static int	ft_is_player_or_space(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	ft_can_escape(char **map, int x, int y, char **visited)
{
	if (x < 0 || y < 0)
		return (1);
	if (!visited[y] || !map[y])
		return (1);
	if (!map[y][x])
		return (1);
	if (map[y][x] == ' ' || map[y][x] == '\n')
		return (1);
	if (map[y][x] == '1' || visited[y][x] == '1')
		return (0);
	visited[y][x] = '1';
	if (ft_can_escape(map, x + 1, y, visited))
		return (1);
	if (ft_can_escape(map, x - 1, y, visited))
		return (1);
	if (ft_can_escape(map, x, y + 1, visited))
		return (1);
	if (ft_can_escape(map, x, y - 1, visited))
		return (1);
	return (0);
}

static int	ft_check_position(char **map, int i, int j, char **visited)
{
	if (!ft_is_player_or_space(map[i][j]))
		return (1);
	ft_reset_visited(visited);
	if (ft_can_escape(map, j, i, visited))
		return (0);
	return (1);
}

static int	ft_process_map_line(char **map, int i, char **visited)
{
	int	j;

	j = 0;
	while (map[i][j])
	{
		if (!ft_check_position(map, i, j, visited))
			return (0);
		j++;
	}
	return (1);
}

int	check_map_boundaries(char **map, int start_i)
{
	int		i;
	int		height;
	int		max_len;
	char	**visited;
	int		result;

	while (map[start_i] && map[start_i][0] == '\n')
		start_i++;
	if (!map[start_i])
		return (0);
	ft_get_map_dims(map + start_i, &height, &max_len);
	visited = ft_alloc_visited(height, max_len);
	if (!visited)
		return (0);
	i = 0;
	result = 1;
	while (map[start_i + i])
	{
		if (!ft_process_map_line(map + start_i, i, visited))
		{
			result = 0;
			break;
		}
		i++;
	}
	free_tab(visited);
	return (result);
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
