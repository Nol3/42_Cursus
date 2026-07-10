NAME = minishell
FLAGS = -Wall -Werror -Wextra -g
FILES = $(shell find src -type f -name "*.c")
OBJS = $(FILES:.c=.o)
DATE = $(shell /usr/bin/date)
LIBFT = ./libft/libft.a

all :$(NAME)

$(NAME) : $(OBJS)
	$(MAKE) -C ./libft
	@gcc $(FLAGS) $(OBJS) -lreadline $(LIBFT) -o $(NAME)

src/%.o : src/%.c
	gcc $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	$(MAKE) -C ./libft clean

fclean:
	@rm -f $(NAME) $(OBJS)
	$(MAKE) -C ./libft fclean

re: fclean all

git:
	git add .
	git commit -m "Daily sync $(DATE)"
	git push origin main

.PHONY: re all fclean clean git

#!/bin/bash

# while true
# do
#     DATE=$(date)
#     git add .
#     git commit -m "Daily sync $DATE"
#     git push origin main
#     sleep 3600
# done
