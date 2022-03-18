/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereda- <rpereda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:48:31 by rpereda-          #+#    #+#             */
/*   Updated: 2022/03/18 15:12:51 by rpereda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void handle_errors(t_vars *vars)
{
	int i;
	int j;
	map_shape_checker(vars);
	
	i = 0;
	while(vars->map[i])
	{
		j = 0;
		while(vars->map[i][j])
		{
			if(vars->map[i][j] != '1' && vars->map[i][j] != '0' && vars->map[i][j] != 'C' 
				&& vars->map[i][j] != 'E' && vars->map[i][j] != '\n' && vars->map[i][j] != 'P')
			{
				write(1,"error\n ya no se ni cual es este pero algo habras hecho",55);
				// get_out(vars);
				exit(1);		
			}
			if (vars->map[i][j] == 'E')
				vars->exit_checker = 1;
			if (vars->map[i][j] == 'P')
				vars->character_checker += 1;
			if (vars->map[i][j] == 'C')
				vars->max_collectibles += 1;
			j++;
		}
		i++;
	}
	assets_checker(vars);
	delimitators_error(vars);
}

void delimitators_error(t_vars *vars)
{
	int len;
	int i;
	int j;
	
	i = 0;
	j = 0;
	len = ft_strlen(vars->map[i]);
	while(vars->map[0][j])
	{
		if (vars->map[0][j] != '1')
		{
			write(1,"error\nno me la cuelas",22);
			// get_out(vars);
			exit(0);
		}
		j++;
	}
	j = 0;
	while(vars->map[vars->img_height - 1][j])
	{
		if (vars->map[vars->img_height - 1][j] != '1')
		{
			write(1,"error\nno me la cuelas",22);
			//get_out(vars);
			exit(0);
		}
		j++;
	}
	while(i < vars->img_height)
	{
		if(vars->map[i][0] != '1' || vars->map[i][len - 1] != '1')
		{
			//liberar matriz usar uncion get out
			write(1,"error\nno me la cuelas",22);
			//get_out(vars);
			exit(0);
		}
		i++;
	}
}
void map_shape_checker (t_vars *vars)
{
	if (vars->img_height == vars->img_width)
	{
		write(1,"error\nel mapa no es rectangular XD",35);
		//get_out(vars);
		exit(0);
	}
}
void assets_checker (t_vars *vars)
{
	if (vars->character_checker != 1 || !(vars->exit_checker) || !(vars->max_collectibles))
	{
		write(1,"error\nnoy ha suficientes elementos en el mapa",46);
		//get_out(vars);
		exit(0);
	}
}

//TODO arreglar segfault cuando hay \n en mitad del mapa