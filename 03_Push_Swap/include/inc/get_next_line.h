/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:11:34 by alcarden          #+#    #+#             */
/*   Updated: 2023/05/25 21:25:40 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

int		ft_strlen(char *str);
char	*ft_strjoin(char *buff, char *stack);
char	*ft_strchr(char *str, char c);
char	*ft_get_line(char *stack);
char	*ft_stack_refill(char *stack);
char	*ft_read_file(char *stack, int fd);
char	*get_next_line(int fd);

#endif