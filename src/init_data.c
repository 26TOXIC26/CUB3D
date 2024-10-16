/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:40:17 by amousaid          #+#    #+#             */
/*   Updated: 2024/10/15 18:20:53 by ana              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void take_xpm(t_mlx *mlx, int *i)
{
	mlx->data->xpms = malloc(sizeof(char *) * 5);
	if (!mlx->data->xpms)
	{
		ft_error("Error:  Memory allocation failed");
		free_mlxs(mlx);
		exit(1);
	}
	while (mlx->data->cub_file[*i])
	{
		if (!ft_strncmp("NO ", mlx->data->cub_file[*i], 3))
			mlx->data->xpms[0] = ft_substr(mlx->data->cub_file[*i], 3, ft_strlen(mlx->data->cub_file[*i]) - 4);
		else if (!ft_strncmp("SO ", mlx->data->cub_file[*i], 3))
			mlx->data->xpms[1] = ft_substr(mlx->data->cub_file[*i], 3, ft_strlen(mlx->data->cub_file[*i]) - 4);
		else if (!ft_strncmp("WE ", mlx->data->cub_file[*i], 3))
			mlx->data->xpms[2] = ft_substr(mlx->data->cub_file[*i], 3, ft_strlen(mlx->data->cub_file[*i]) - 4);
		else if (!ft_strncmp("EA ", mlx->data->cub_file[*i], 3))
		{
			mlx->data->xpms[3] = ft_substr(mlx->data->cub_file[*i], 3, ft_strlen(mlx->data->cub_file[*i]) - 4);
			(*i)++;
			break ;
		}
		(*i)++;
	}
	mlx->data->xpms[4] = NULL;
}

void take_colors(t_mlx *mlx, int *i)
{
	char **rgb;

	while (mlx->data->cub_file[*i])
	{
		if (!ft_strncmp("F ", mlx->data->cub_file[*i], 2))
		{
			rgb = ft_split(&mlx->data->cub_file[*i][3], ',');
			mlx->data->colors[0][0] = ft_atoi(rgb[0]);
			mlx->data->colors[0][1] = ft_atoi(rgb[1]);
			mlx->data->colors[0][2] = ft_atoi(rgb[2]);
			free_tab(rgb);
		}
		else if (!ft_strncmp("C ", mlx->data->cub_file[*i], 2))
		{
			rgb = ft_split(&mlx->data->cub_file[*i][3], ',');
			mlx->data->colors[1][0] = ft_atoi(rgb[0]);
			mlx->data->colors[1][1] = ft_atoi(rgb[1]);
			mlx->data->colors[1][2] = ft_atoi(rgb[2]);
			free_tab(rgb);
			(*i)++;
			break ;
		}
		(*i)++;
		}
}

void take_map (t_mlx *mlx, int *i)
{
	int j;
	int size;
	int width;
	int k;

	size = d2_len(&mlx->data->cub_file[*i]);
	mlx->data->map2d = malloc(sizeof(char *) * (size + 1));
	if (!mlx->data->map2d)
	{
		ft_error("Error:  Memory allocation failed");
		free_mlxs(mlx);
		exit(1);
	}
	j = 0;
	width = ft_strlen(mlx->data->cub_file[*i]);
	k = *i;
	while (mlx->data->cub_file[k] && mlx->data->cub_file[k][0] != '\n')
	{
		if (ft_strlen(mlx->data->cub_file[k]) > width)
			width = ft_strlen(mlx->data->cub_file[k]);
		k++;
	}
	while (mlx->data->cub_file[*i] && mlx->data->cub_file[*i][0] != '\n')
	{
		mlx->data->map2d[j] = ft_strdup_max(mlx->data->cub_file[*i], width);
		(*i)++;
		j++;
	}
	mlx->data->map2d[j] = NULL;
}
