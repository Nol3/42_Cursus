# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alcarden <alcarden@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 19:01:46 by alcarden          #+#    #+#              #
#    Updated: 2023/10/25 19:37:32 by alcarden         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET = $(BIN_DIR)/libft.a

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
		ft_split.c\
		ft_lstnew_bonus.c\
		ft_lstadd_front_bonus.c\
		ft_lstsize_bonus.c\
		ft_lstlast_bonus.c\
		ft_lstadd_back_bonus.c\
		ft_lstdelone_bonus.c\
		ft_lstclear_bonus.c\
		ft_lstiter_bonus.c\
		ft_lstmap_bonus.c\
		ft_char_str.c\
		ft_decimals.c\
		ft_nums.c\
		ft_printf.c\
		ft_ptr.c\
		ft_put_hex.c\
		get_next_line.c\
		get_next_line_utils.c\
		get_next_line_bonus.c\
		get_next_line_utils_bonus.c\

OBJS = $(addprefix $(OBJ_DIR)/,$(FILES:%.c=%.o))

INC_DIR = ./inc
OBJ_DIR = ./obj
SRC_DIR = ./src
BIN_DIR = ./bin

CFLAGS = -Wall -Wextra -Werror

$(TARGET): $(OBJS)
	mkdir -p $(BIN_DIR)
	ar rcs $(TARGET) $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	gcc $(CFLAGS) -I$(INC_DIR) -c $< -o $@

.PHONY: all clean fclean re

all: $(TARGET)

clean:
	@if [ -d $(OBJ_DIR) ]; then \
		rm -r $(OBJ_DIR); \
	fi

fclean: clean
	@if [ -d $(BIN_DIR) ]; then \
		rm -r $(BIN_DIR); \
	fi

re: fclean all