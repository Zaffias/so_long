/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereda- <rpereda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:33:30 by rpereda-          #+#    #+#             */
/*   Updated: 2022/03/16 18:27:50 by rpereda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
 #define SO_LONG_H

 #include <stdio.h>
 #include <unistd.h>
 #include <stdlib.h>
 #include <fcntl.h>
 #include "./GetNextLine/get_next_line.h"
 typedef struct	s_vars {
	int		pos[2];
	int		winsize[2];
	void	*mlx;
	void	*win;
	void	*character;
	void	*obstacle;
	void	*collectible;
	void	*exit;
	char	*addr;
	char	*path;
	int		img_width;
	int		img_height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
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
	SIZE = 32,        
};


#endif