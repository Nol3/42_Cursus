/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:29:45 by alcarden          #+#    #+#             */
/*   Updated: 2023/05/17 16:56:06 by alcarden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>

int	ft_printf(char const *str, ...);
int	ft_count_chars(const char *str);
int	ft_check_format(va_list params, char c);
int	ft_putchar(char c);
int	ft_putstr(char *str);
int	ft_putptr(long unsigned int ptr);
int	ft_puthexp(long unsigned int ptr, int num);
int	ft_count_hex(long unsigned int num);
int	ft_putnbr(int num);
int	ft_count_digits(int num);
int	ft_digitsu(unsigned int num);
int	ft_putud(unsigned int num);
int	ft_puthex(char c, unsigned int num);

#endif