# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/18 18:01:17 by alcarden          #+#    #+#              #
#    Updated: 2023/04/27 19:30:49 by alcarden         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Werror -Wextra

FILES = ft_atoi.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_strlcat.c\
		ft_strncmp.c\
		ft_tolower.c\
		ft_toupper.c\
		ft_strlcpy.c\
		ft_memmove.c\
		ft_memset.c\
		ft_memcpy.c\
		ft_memcmp.c\
		ft_strnstr.c\
		ft_strlen.c\
		ft_bzero.c\
		ft_memchr.c\
		ft_strrchr.c\
		ft_strchr.c\
		ft_calloc.c\
		ft_strdup.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_strmapi.c\
		ft_striteri.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_itoa.c\
		ft_split.c

OBJ = $(FILES:.c=.o)

BONUS = ft_lstnew_bonus.c\
		ft_lstadd_front_bonus.c\
		ft_lstsize_bonus.c\
		ft_lstlast_bonus.c\
		ft_lstadd_back_bonus.c\
		ft_lstdelone_bonus.c\
		ft_lstclear_bonus.c\
		ft_lstiter_bonus.c\
		ft_lstmap_bonus.c

BOBJECTS=$(BONUS:.c=.o)

FLAGS = -Wall -Wextra -Werror

all :$(NAME)

$(NAME) : $(OBJ)
	@ar rcs $(NAME) $(OBJ)

$(OBJ) : $(FILES)
	@gcc $(FLAGS) -c $(FILES)

bonus:
	@gcc $(FLAGS) -c $(BONUS)
	@ar rcs $(NAME) $(BOBJECTS)

clean:
	@rm -f $(OBJ) $(BOBJECTS)

fclean:
	@rm -f $(NAME) $(OBJ) $(BOBJECTS)

re: fclean all

.PHONY: re all fclean clean bonus