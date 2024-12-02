/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouboul <ebouboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:06:32 by amousaid          #+#    #+#             */
/*   Updated: 2024/12/01 23:13:38 by ebouboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

// void free_mlxs(t_mlx *mlx)
// {
// 	if (mlx->data->cub_file)
// 		free_tab(mlx->data->cub_file);
// 	if (mlx->data->xpms)
// 		free_tab(mlx->data->xpms);
// 	if (mlx->data->map2d)
// 		free_tab(mlx->data->map2d);
// 	if (mlx->size)
// 		free(mlx->size);
// 	if (mlx->data)
// 		free(mlx->data);
// 	// if (mlx->ply)
// 	// 	free(mlx->ply);
// 	// if (mlx->ray)
// 	// 	free(mlx->ray);
// 	// if (mlx->tex)
// 	// 	free(mlx->tex);
// 	// if (mlx->mlx)
// 	// 	free(mlx->mlx);
// 	// free(mlx);
// }

// void	free_tab(void **tab)
// {
// 	size_t	i;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// 	if (tab)
// 	{
// 		free(tab);
// 		tab = NULL;
// 	}
// }

// static void	free_texinfo(t_texinfo *textures)
// {
// 	if (textures->north)
// 		free(textures->north);
// 	if (textures->south)
// 		free(textures->south);
// 	if (textures->west)
// 		free(textures->west);
// 	if (textures->east)
// 		free(textures->east);
// 	if (textures->floor)
// 		free(textures->floor);
// 	if (textures->ceiling)
// 		free(textures->ceiling);
// }

// static void	free_map(t_data *data)
// {
// 	if (data->mapinfo.fd > 0)
// 		close(data->mapinfo.fd);
// 	if (data->mapinfo.file)
// 		free_tab((void **)data->mapinfo.file);
// 	if (data->map)
// 		free_tab((void **)data->map);
// }

// int	free_data(t_data *data)
// {
// 	if (data->textures)
// 		free_tab((void **)data->textures);
// 	if (data->texture_pixels)
// 		free_tab((void **)data->texture_pixels);
// 	free_texinfo(&data->texinfo);
// 	free_map(data);
// 	return (FAILURE);
// }


void	clean_exit(t_data *data, int code)
{
	if (!data)
		exit(code);
	if (data->win && data->mlx)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		mlx_loop_end(data->mlx);
		free(data->mlx);
	}
	// free_data(data);
	exit(code);
}

int	quit_cub3d(t_data *data)
{
    (void)data;
	clean_exit(data, 0);
	return (0);
}

int	err_msg(char *detail, char *str, int code)
{
	ft_putstr_fd("cub3D: Error", 2);
	if (detail)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(detail, 2);
	}
	if (str)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
	}
	ft_putstr_fd("\n", 2);
	return (code);
}

int	err_msg_val(int detail, char *str, int code)
{
    (void)detail;
	ft_putstr_fd("cub3D: Error: ", 2);
	// ft_putnbr_fd(detail, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (code);
}
