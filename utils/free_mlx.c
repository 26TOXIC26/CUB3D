/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:06:32 by amousaid          #+#    #+#             */
/*   Updated: 2024/10/12 15:07:08 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

void free_mlxs(t_mlx *mlx)
{
	if (mlx->data->cub_file)
		free_tab(mlx->data->cub_file);
	if (mlx->data->xpms)
		free_tab(mlx->data->xpms);
	free(mlx->data);
		free(mlx);
}
