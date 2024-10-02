/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:15:33 by amousaid          #+#    #+#             */
/*   Updated: 2024/10/02 19:36:36 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int check_exten(char *str, char *exten)
{
	int i;

	i = ft_strlen(str);
	if (ft_strcmp(&str[i - 5], exten))
	{
		ft_error("Error:  Invalid file extension");
		return (0);
	}
	return (1);
}
int		check_texture(char **map, int *i)
{
	int valid;

	valid = 0;
	while (map[*i])
	{
		if (map[*i][0] == '\n')
		{
			(*i)++;
			continue ;
		}
		if (map[*i][0] == '\0')
			return (1);
		if (ft_strncmp("NO ", map[*i], 3) == 0 && valid == 0 && check_exten(map[*i], ".xpm\n"))
			valid = 1;
		else if (ft_strncmp("SO ", map[*i], 3) == 0 && valid == 1 && check_exten(map[*i], ".xpm\n"))
			valid = 2;
		else if (ft_strncmp("WE ", map[*i], 3) == 0 && valid == 2 && check_exten(map[*i], ".xpm\n"))
			valid = 3;
		else if (ft_strncmp("EA ", map[*i], 3) == 0 && valid == 3 && check_exten(map[*i], ".xpm\n"))
			valid = 4;
		else
			break ;
		(*i)++;
		if (valid == 4)
			return (1);
	}
	return (0);
}

