/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereda- <rpereda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:29:02 by rpereda-          #+#    #+#             */
/*   Updated: 2022/03/18 17:46:03 by rpereda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "so_long.h"

void init_character(t_vars *vars)
{
	int i;
	int j;
	int flag;
	int found;

	flag = 1;
	i = 0;
	while(vars->map[i] && flag)
	{
		j = 0;
		while(vars->map[i][j])
		{
			if (vars->map[i][j] == 'P')
			{
				flag = 0;
				found = i;
				break;
			}	
			j++;
		}
		i++;
	}
	vars->charpos[1] = found;
	vars->charpos[0] = j;
	vars->pos[0] = vars->charpos[0] * SIZE;
	vars->pos[1] = vars->charpos[1] * SIZE;
}

void init(t_vars *vars)
{
	vars->charpos[0] = 0;
	vars->charpos[1] = 0;
	vars->collectibles = 0;
	vars->winsize[0] = SIZE;
	vars->winsize[1] = SIZE;
	vars->img_height = 0;
	vars->img_width = 0;
	vars->character_checker = 0;
	vars->exit_checker = 0;
	vars->max_collectibles = 0;
}
void load_images(t_vars *vars)
{
	vars->character = mlx_xpm_file_to_image(vars->mlx, "./images/my_man.xpm", &(vars->img_width), &(vars->img_height));
	vars->obstacle = mlx_xpm_file_to_image(vars->mlx,"./images/obstacle.xpm", &(vars->img_width), &(vars->img_height));
	vars->floor = mlx_xpm_file_to_image(vars->mlx,"./images/floor.xpm", &(vars->img_width), &(vars->img_height));
	//TODO añadir resto de images
	//TODO buscar imagenes XD!
}

void check_exit (t_vars *vars, int x, int y)
{
	if (vars->map[x][y] == 'E' && vars->collectibles == vars->max_collectibles)
	{
		write(1,"gg",2);
		exit(0);
	}
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

int		get_out(t_vars *vars)
{
	//rehacer funcion de mierda XD!
	
	int i;
	i = vars->img_height - 1;
	while(vars->map[i])
	{
		free(vars->map[i]);
		i--;
	}
	free(vars->map);
	exit(0);
	return (0);
}

int	movement(int keycode, t_vars *vars)
{
	//arreglar esta cosa
	if(keycode == ESC){
		mlx_destroy_window(vars->mlx, vars->win);
		//free(vars->map_str);
		exit(0);
	}
	if (keycode == D && vars->map[vars->charpos[1]][vars->charpos[0] + 1] != '1')
	{
			if(vars->map[vars->charpos[1]][vars->charpos[0] + 1] == 'C')
			{
				vars->collectibles++;
				vars->map[vars->charpos[1]][vars->charpos[0] + 1] = '0';
			}
			mlx_put_image_to_window(vars->mlx, vars->win, vars->floor, vars->pos[0], vars->pos[1]);
			vars->pos[0] += SIZE;
			vars->charpos[0] += 1;
			mlx_put_image_to_window(vars->mlx, vars->win, vars->character, vars->pos[0], vars->pos[1]);
	}
	if (keycode == A)
	{
		if(vars->map[vars->charpos[1]][vars->charpos[0] - 1] != '1')
		{
			if(vars->map[vars->charpos[1]][vars->charpos[0] - 1] == 'C')
			{
				vars->collectibles++;
				vars->map[vars->charpos[1]][vars->charpos[0] - 1] = '0';
			}
			mlx_put_image_to_window(vars->mlx, vars->win, vars->floor, vars->pos[0], vars->pos[1]);
			vars->pos[0] -= SIZE;
			vars->charpos[0] -= 1;
			mlx_put_image_to_window(vars->mlx, vars->win, vars->character, vars->pos[0], vars->pos[1]);
		}
	}
	
	if (keycode == W){
		if(vars->map[vars->charpos[1] - 1][vars->charpos[0]] != '1')
		{
			if(vars->map[vars->charpos[1] - 1][vars->charpos[0]] == 'C')
			{
				vars->collectibles++;
				vars->map[vars->charpos[1] - 1][vars->charpos[0]] = '0';
			}
			mlx_put_image_to_window(vars->mlx, vars->win, vars->floor, vars->pos[0], vars->pos[1]);
			vars->pos[1] -= SIZE;
			vars->charpos[1] -= 1;
			mlx_put_image_to_window(vars->mlx, vars->win, vars->character, vars->pos[0], vars->pos[1]);		
		}
	}
	
	if (keycode == S){
		if(vars->map[vars->charpos[1] + 1][vars->charpos[0]] != '1')
		{
			if(vars->map[vars->charpos[1] + 1][vars->charpos[0]] == 'C')
			{
				vars->collectibles++;
				vars->map[vars->charpos[1] + 1][vars->charpos[0]] = '0';
			}
			mlx_put_image_to_window(vars->mlx, vars->win, vars->floor, vars->pos[0], vars->pos[1]);
			vars->pos[1] += SIZE;
			vars->charpos[1] += 1;
			mlx_put_image_to_window(vars->mlx, vars->win, vars->character, vars->pos[0], vars->pos[1]);		
		}
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
	init_character(&vars);
	mlx_key_hook(vars.win, movement, &vars);
	mlx_hook(vars.win, 17, 1L << 17, get_out, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

//TODO SALTO DE LINEA EN EL MAPA = BOOM
//TODO SOLO ACEPTAR ARCHIVOS CON LA TERMINACION .BER
//TODO IMPLEMENTAR LA SALIDA Y YA ESTARÍA XD