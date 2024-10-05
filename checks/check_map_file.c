/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:15:33 by amousaid          #+#    #+#             */
/*   Updated: 2024/10/05 10:35:55 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_exten(char *str, char *exten)
{
	int	i;

	i = ft_strlen(str);
	if (ft_strcmp(&str[i - 5], exten))
		return (0);
	return (1);
}

int	check_texture(char **map, int *i)
{
	int	valid;

	valid = 0;
	while (map[*i] && valid < 4)
	{
		if (map[*i][0] == '\n')
		{
			(*i)++;
			continue ;
		}
		else if (!ft_strncmp("NO ", map[*i], 3) && valid == 0
			&& check_exten(map[*i], ".xpm\n"))
			valid++;
		else if (!ft_strncmp("SO ", map[*i], 3) && valid == 1
			&& check_exten(map[*i], ".xpm\n"))
			valid++;
		else if (!ft_strncmp("WE ", map[*i], 3) && valid == 2
			&& check_exten(map[*i], ".xpm\n"))
			valid++;
		else if (!ft_strncmp("EA ", map[*i], 3) && valid == 3
			&& check_exten(map[*i], ".xpm\n"))
			valid++;
		else
			return (ft_error("Error:  Invalid texture"), 0);
		(*i)++;
	}
	return (1);
}

int	check_num(char **rgb)
{
	int	i;
	int	j;

	i = 0;
	while (rgb[i])
	{
		j = 0;
		while (rgb[i][j])
		{
			if (!ft_isdigit(rgb[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	i = 0;
	while (rgb[i])
	{
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			return (1);
		i++;
	}
	return (0);
}

int	check_rgb(char *str)
{
	char	**rgb;
	char	*rgb_str;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n' && str[i] == ' ')
		i++;
	if (!str[i] || str[i] == '\n')
		return (0);
	rgb_str = ft_substr(str, i, ft_strlen(str) - i - 1);
	rgb = ft_split(rgb_str, ',');
	if (d2_len(rgb) != 3 || check_num(rgb))
		return (free_tab(rgb), free(rgb_str), 0);
	return (free_tab(rgb), free(rgb_str), 1);
}

int	check_colors(char **map, int *i)
{
	int	valid;

	valid = 0;
	while (map[*i] && valid < 2)
	{
		if (map[*i][0] == '\n')
		{
			(*i)++;
			continue ;
		}
		else if (!ft_strncmp("F ", map[*i], 2) && valid == 0
			&& check_rgb(&map[*i][3]))
			valid++;
		else if (!ft_strncmp("C ", map[*i], 2) && valid == 1
			&& check_rgb(&map[*i][3]))
			valid++;
		else
			return (ft_error("Error:  Invalid color"), 0);
		(*i)++;
	}
	return (1);
}
