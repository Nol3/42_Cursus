/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:25:22 by alcarden          #+#    #+#             */
/*   Updated: 2023/10/25 15:46:19 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/inc/libft.h"

/**
 * @brief funcion para salida de errores
 *
 */
void	ft_error(void);

/**
 * @brief funcion que encuentra la ruta del comando
 * Función que buscará la línea de ruta dentro del entorno, se
   dividirá y probará cada ruta de comando y luego devolverá la correcta.
 *
 * @param cmd //comando limpio con split. (argv[2])
 * @param envp
 */
char	*ft_find_path(char *cmd, char **envp);

/**
 * @brief funcion que ejecuta el comando
 *
 * Función que toma el comando y lo envía a find_path
 antes de ejecutarlo.
 *
 * @param argv
 * @param envp
 */
void	ft_execute(char *argv, char **envp);

/**
 * @brief funcion que ejecuta el proceso hijo
 * Proceso hijo que se ejecuta dentro de un fork, toma el filein, pone la
   salida dentro la pipe y luego se cierra con la función exec
 *
 * @param argv
 * @param envp
 * @param fd
 */
void	ft_child_process(char **argv, char **envp, int *fd);

/**
 * @brief funcion que ejecuta el proceso padre
 *
 * Proceso padre que toma los datos de la pipe, cambia la salida por el
   fileout y también cierra con la función exec
 *
 * @param argv
 * @param envp
 * @param fd
 */
void	ft_parent_process(char **argv, char **envp, int *fd);

#endif
