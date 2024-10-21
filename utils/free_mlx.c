/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana <ana@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:06:32 by amousaid          #+#    #+#             */
/*   Updated: 2024/10/15 18:26:55 by ana              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void free_mlxs(t_mlx *mlx)
{
	if (mlx->data->cub_file)
		free_tab(mlx->data->cub_file);
	if (mlx->data->xpms)
		free_tab(mlx->data->xpms);
	if (mlx->data->map2d)
		free_tab(mlx->data->map2d);
	if (mlx->size)
		free(mlx->size);
	if (mlx->data)
		free(mlx->data);
	// free(mlx);
}
