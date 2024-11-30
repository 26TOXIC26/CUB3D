/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouboul <ebouboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:40:17 by amousaid          #+#    #+#             */
/*   Updated: 2024/11/30 05:29:25 by ebouboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void take_xpm(t_data *data, int *i)
{
	data->xpms = malloc(sizeof(char *) * 5);
	if (!data->xpms)
	{
		ft_error("Error:  Memory allocation failed");
		// free_mlxs(mlx);
		exit(1);
	}
	while (data->cub_file[*i])
	{
		if (!ft_strncmp("NO ", data->cub_file[*i], 3))
			data->xpms[0] = ft_substr(data->cub_file[*i], 3, ft_strlen(data->cub_file[*i]) - 4);
		else if (!ft_strncmp("SO ", data->cub_file[*i], 3))
			data->xpms[1] = ft_substr(data->cub_file[*i], 3, ft_strlen(data->cub_file[*i]) - 4);
		else if (!ft_strncmp("WE ", data->cub_file[*i], 3))
			data->xpms[2] = ft_substr(data->cub_file[*i], 3, ft_strlen(data->cub_file[*i]) - 4);
		else if (!ft_strncmp("EA ", data->cub_file[*i], 3))
		{
			data->xpms[3] = ft_substr(data->cub_file[*i], 3, ft_strlen(data->cub_file[*i]) - 4);
			(*i)++;
			break ;
		}
		(*i)++;
	}
	data->xpms[4] = NULL;
}

void take_colors(t_data *data, int *i)
{
	char **rgb;

	while (data->cub_file[*i])
	{
		if (!ft_strncmp("F ", data->cub_file[*i], 2))
		{
			rgb = ft_split(&data->cub_file[*i][3], ',');
			data->colors[0][0] = ft_atoi(rgb[0]);
			data->colors[0][1] = ft_atoi(rgb[1]);
			data->colors[0][2] = ft_atoi(rgb[2]);
			free_tab(rgb);
		}
		else if (!ft_strncmp("C ", data->cub_file[*i], 2))
		{
			rgb = ft_split(&data->cub_file[*i][3], ',');
			data->colors[1][0] = ft_atoi(rgb[0]);
			data->colors[1][1] = ft_atoi(rgb[1]);
			data->colors[1][2] = ft_atoi(rgb[2]);
			free_tab(rgb);
			(*i)++;
			break ;
		}
		(*i)++;
		}
}

void take_map (t_data *data, int *i)
{
	int j;
	int size;
	int width;
	int k;

	size = d2_len(&data->cub_file[*i]);
	data->map = malloc(sizeof(char *) * (size + 1));
	if (!data->map)
	{
		ft_error("Error:  Memory allocation failed");
		// free_mlxs(mlx);
		exit(1);
	}
	j = 0;
	width = ft_strlen(data->cub_file[*i]);
	k = *i;
	while (data->cub_file[k] && data->cub_file[k][0] != '\n')
	{
		if (ft_strlen(data->cub_file[k]) > width)
			width = ft_strlen(data->cub_file[k]);
		k++;
	}
	while (data->cub_file[*i] && data->cub_file[*i][0] != '\n')
	{
		data->map[j] = ft_strdup_max(data->cub_file[*i], width);
		(*i)++;
		j++;
	}
	data->map[j] = NULL;
}
