/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereda- <rpereda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:06:53 by rpereda-          #+#    #+#             */
/*   Updated: 2022/03/01 13:52:39 by rpereda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

int		size_malloc(char *buffer);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
int		ft_strchr(char *str, int c);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);

#endif
