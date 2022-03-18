/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereda- <rpereda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:33:30 by rpereda-          #+#    #+#             */
/*   Updated: 2022/03/18 16:37:44 by rpereda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
 #define SO_LONG_H

 #include <stdio.h>
 #include <unistd.h>
 #include <stdlib.h>
 #include <fcntl.h>
 #include "./libft/libft.h"
 
 typedef struct	s_vars {
	int		pos[2];
	int		charpos[2];
	int		winsize[2];
	void	*mlx;
	void	*win;
	void	*character;
	void	*obstacle;
	void	*collectible;
	void	*exit;
	void	*floor;
	int		img_width;
	int		img_height;
	char	*map_str;
	char	**map;
	int		max_collectibles;
	int		exit_checker;
	int		character_checker;
	int		collectibles;
}	t_vars;

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17,
	W = 13,
	A = 0,
	S = 1,
	D = 2,
	ESC = 53,
	SPC = 49,
	SIZE = 100,        
};

//error handling
 void 	handle_errors(t_vars *vars);
 void 	delimitators_error(t_vars *vars);
 void 	map_shape_checker (t_vars *vars);
 void 	assets_checker (t_vars *vars);
 int	get_out(t_vars *vars);
 //movement y  eso
 int	movement (int keycode, t_vars *vars);
 void 	draw_map (t_vars *vars);
//----------
#endif