/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereda- <rpereda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:29:02 by rpereda-          #+#    #+#             */
/*   Updated: 2022/03/17 15:08:06 by rpereda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "so_long.h"

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
			//liberar matriz
			exit(1);
		}
		j++;
	}
	j = 0;
	while(vars->map[vars->img_height - 1][j])
	{
		if (vars->map[vars->img_height - 1][j] != '1')
		{
			//liberar matriz usar funcion get out
			exit(1);
		}
		j++;
	}
	while(i < vars->img_height)
	{
		if(vars->map[i][0] != '1' || vars->map[i][len - 1] != '1')
		{
			//liberar matriz usar uncion get out
			write(1,"ta mal",6);
			exit(1);
		}
		i++;
	}
}
void handle_errors(t_vars *vars)
{
	int i;
	int j;
	if (vars->img_height == vars->img_width)
	{
		//free(vars->map_str); liberar matriz
		exit(1);
	}
	i = 0;
	while(vars->map[i])
	{
		j = 0;
		while(vars->map[i][j])
		{
			if(vars->map[i][j] != '1' && vars->map[i][j] != '0' && vars->map[i][j] != 'C' 
				&& vars->map[i][j] != 'E' && vars->map[i][j] != '\n' && vars->map[i][j] != 'P')
			{
				//free(vars->map_str); liberar matriz
				write(1,"error",5);
				exit(1);		
			}
			j++;
		}
		i++;
	}
	delimitators_error(vars);
}
void init(t_vars *vars){
	int i;
	int j;
	
	i = 0;
	// while(vars->map[i])
	// {
	// 	j = 0;
	// 	while(vars->map[i][j] != 'P')
	// 		j++;
	// 	i++;
	// }
	//printf("%d, %d\n", i , j);
	// vars->pos[0] = i;
	// vars->pos[1] = j;
	vars->winsize[0] = SIZE;
	vars->winsize[1] = SIZE;
	vars->img_height = 0;
	vars->img_width = 0;
}
void load_images(t_vars *vars)
{
	vars->character = mlx_xpm_file_to_image(vars->mlx, "./images/my_man.xpm", &(vars->img_width), &(vars->img_height));
	vars->obstacle = mlx_xpm_file_to_image(vars->mlx,"./images/obstacle.xpm", &(vars->img_width), &(vars->img_height));
	vars->floor = mlx_xpm_file_to_image(vars->mlx,"./images/floor.xpm", &(vars->img_width), &(vars->img_height));
	//TODO añadir resto de images
	//TODO buscar imagenes XD!
}

void matrix(int fd, t_vars *vars, char *path)
{
	char	buffer[8];
	int		bytes;
	int		stop;

	bytes = read(fd, buffer,8);
	while (bytes != stop)
	{
		stop = bytes;
		bytes += read(fd,buffer,8);
	}
	vars->map_str = malloc(sizeof(char) * bytes + 1);
	close(fd);
	fd = open(path, 0);
	read(fd, vars->map_str, bytes);
	vars->map_str[bytes + 1] = 0;
	while(vars->map_str[vars->img_width])
	{
		if(vars->map_str[vars->img_width] == '\n')
			vars->img_height++;
		vars->img_width++;
	}
	vars->img_height++;
	vars->img_width /= vars->img_height;
	vars->map = ft_split(vars->map_str, '\n');
	free(vars->map_str);
}

int	get_out(t_vars *vars)
{
	//free(vars->map_str); cambiar por liberal la matriz
	exit(0);
	return(0);
}

int	movement(int keycode, t_vars *vars)
{
	//arreglar esta cosa
	if(keycode == ESC){
		mlx_destroy_window(vars->mlx, vars->win);
		//free(vars->map_str);
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
void draw_map(t_vars *vars)
{
	int i;
	int j;
	i = 0;

	while (vars->map[i])
	{
		j = 0;
		while(vars->map[i][j])
		{
			if (vars->map[i][j])
				mlx_put_image_to_window(vars->mlx, vars->win, vars->floor, SIZE * j, SIZE * i);
			if (vars->map[i][j] == '1')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->obstacle, SIZE * j, SIZE * i);
			if (vars->map[i][j] == 'P')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->character, SIZE * j, SIZE * i);
			//TODO Descargar estas lindas imagenes
			// if(vars->map[i][j] == 'C')
			// 	mlx_put_image_to_window(vars->mlx, vars->win, vars->collectible, SIZE * j, SIZE * i);
			// if(vars->map[i][j] == 'E')
			// 	mlx_put_image_to_window(vars->mlx, vars->win, vars->exit, SIZE * j, SIZE * i);
			j++;
		}
		i++;
	}
}
int main(int argc, char **argv)
{
	t_vars	vars;
	c_vars	cvars;

	if (argc != 2)
		return (1);
	init(&vars);
	int fd = open(argv[1], 0);
	matrix(fd, &vars , argv[1]);
	handle_errors(&vars);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.winsize[0] * vars.img_width, vars.winsize[1] * vars.img_height, "so_long");
	load_images(&vars);
	draw_map(&vars);
	mlx_key_hook(vars.win, movement, &vars);
	mlx_hook(vars.win, 17, 1L << 17, get_out, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

