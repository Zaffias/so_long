/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereda- <rpereda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:29:02 by rpereda-          #+#    #+#             */
/*   Updated: 2022/03/16 18:27:26 by rpereda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "so_long.h"
void init(t_vars *vars){
	vars->pos[0] = 0;
	vars->pos[1] = 0;
	vars->winsize[0] = SIZE;
	vars->winsize[1] = SIZE;
}
char **matrix(int fd)
{
	char **res;

	int y_size;
	int x_size;
	*res = get_next_line(fd);
	y_size = 1;

	while(*res)
	{
		*res = get_next_line(fd);
		y_size++;
		free(*res); 
	}
	return res;
}

int	movement(int keycode, t_vars *vars)
{

	if(keycode == ESC){
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if (keycode == D){
		vars->pos[0] += SIZE;
		mlx_put_image_to_window(vars->mlx, vars->win, vars->character, vars->pos[0], vars->pos[1]);
	}
	if (keycode == A){
		vars->pos[0] -= SIZE;
		mlx_put_image_to_window(vars->mlx, vars->win, vars->character, vars->pos[0], vars->pos[1]);
	}
	if (keycode == W){
		vars->pos[1] -= SIZE;		
		mlx_put_image_to_window(vars->mlx, vars->win, vars->character, vars->pos[0], vars->pos[1]);
	}
		if (keycode == S){
		vars->pos[1] += SIZE;		
		mlx_put_image_to_window(vars->mlx, vars->win, vars->character, vars->pos[0], vars->pos[1]);
	}
	return (0);
}

int main(int argc, char**argv)
{
	t_vars vars;
	char **culo;
	if (argc != 3)
		return (1);
	
	int fd = open(argv[2],0);
	culo = matrix(fd);
	printf("%s", *culo);
	init(&vars);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.winsize[0],vars.winsize[1], "klk");
	vars.character = mlx_xpm_file_to_image(vars.mlx, "./images/vapo.xpm", &(vars.img_width), &(vars.img_height));
	mlx_put_image_to_window(vars.mlx, vars.win, vars.character, 0, 0);
	mlx_key_hook(vars.win, movement, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
