# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 14:46:05 by alcarden          #+#    #+#              #
#    Updated: 2023/05/17 18:03:40 by alcarden         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CFLAGS = -Wall -Werror -Wextra
FILES = ft_printf.c\
		ft_decimals.c\
		ft_char_str.c\
		ft_nums.c\
		ft_put_hex.c\
		ft_ptr.c

OBJ = $(FILES:.c=.o)

all :$(NAME)

$(NAME) : $(OBJ)
	@ar rcs $(NAME) $(OBJ)

$(OBJ) : $(FILES)
	@gcc $(FLAGS) -c $(FILES)

clean:
	@rm -f $(OBJ)

fclean:
	@rm -f $(NAME) $(OBJ)

re: fclean all

.PHONY: re all fclean clean