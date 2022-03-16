/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereda- <rpereda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:29:02 by rpereda-          #+#    #+#             */
/*   Updated: 2022/03/16 19:29:08 by rpereda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "so_long.h"

void init(t_vars *vars){
	vars->pos[0] = 0;
	vars->pos[1] = 0;
	vars->winsize[0] = SIZE;
	vars->winsize[1] = SIZE;
	vars->img_height = 0;
	vars->img_width = 0;
	
}
char **matrix(int fd, t_vars *vars)
{
	//TODO usar mi strlen :)))))))))
	//TODO como verga reinicio el puto get_next_line sin ser tan cutre de abrir otro XD!
	char **res;

	*res = get_next_line(fd);
	vars->img_width = strlen(*res);
	while(*res)
	{
		*res = get_next_line(fd);
		vars->img_height++;
		free(*res);
	}
	res = malloc(sizeof(char*) * vars->img_height);
	*res = get_next_line(fd);
	res++;
	while(*res)
	{
		*res = get_next_line(fd);
		res++;
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

	init(&vars);
	if (argc != 2)
		return (1);
	int fd = open(argv[1], 0);
	culo = matrix(fd, &vars);
	for (int i = 0; i < vars.img_height; i++){
		printf("%s\n %d\n", culo[i], vars.img_height);
	}
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.winsize[0] * vars.img_width, vars.winsize[1] * vars.img_height, "so_long");
	mlx_put_image_to_window(vars.mlx, vars.win, vars.character, 0, 0);
	mlx_key_hook(vars.win, movement, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

void load_images(t_vars *vars)
{
	vars->character = mlx_xpm_file_to_image(vars->mlx, "./images/vapo.xpm", &(vars->img_width), &(vars->img_height));
	//TODO añadir resto de images
	//TODO buscar imagenes XD!
}

void handle_errors(t_vars *vars)
{
	if (vars->img_height == vars->img_width)
		exit(1);
	//TODO, comprobar que la primera linea, la ultima linea y tanto el primer caracter como el ultimo de todas las lineas sea un 1
}