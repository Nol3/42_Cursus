NAME = push_swap
FLAGS = -Wall -Werror -Wextra -g
FILES = $(shell find src -type f -name "*.c")
LIBFT = include/bin/libft.a
OBJS = $(FILES:.c=.o)

all :$(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	@gcc $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)

src/%.o : src/%.c
	gcc $(FLAGS) -c $< -o $@

$(LIBFT):
	make -C include

clean:
	@rm -f $(OBJS)
	make -C include clean

fclean:
	@rm -f $(NAME) $(OBJS)
	make -C include fclean

re: fclean all

.PHONY: re all fclean clean