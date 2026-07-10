NAME = so_long
FLAGS = -Wall -Wextra -Wextra -g
MLX42 = MLX42/build/libmlx42.a
LIBFT = include/bin/libft.a
LIBS = -ldl -lglfw3 -pthread -lm $(MLX42)/libmlx42.a

SRCS	=	./src/main.c \
			./src/create.c \
			./src/init.c \
			./src/map_check.c \
			./src/map_load.c \
			./src/outs.c \
			./src/png_to_textures.c \
			./src/solve.c \
			./src/textures_to_window.c \
			./src/wall_and_floor.c \
			./src/validate.c \
			./src/move.c \
			./src/valere_move.c

OBJS	= ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(LIBFT) $(MLX42) $(OBJS)
	@gcc $(FLAGS) $(OBJS) $(MLX42) $(LIBFT) -Iinclude -ldl -lglfw -pthread -lm -o $(NAME)
	# @gcc $(FLAGS) $(OBJS) $(MLX42) $(LIBFT) -framework Cocoa -framework OpenGL -framework IOKit -Iinclude -lglfw -L "/Users/alcarden/.brew/opt/glfw/lib/" -o $(NAME)

src/%.o : src/%.c
	gcc $(FLAGS) -c $< -o $@

$(MLX42):
	make -C MLX42
$(LIBFT):
	make -C include

clean:
	@rm -f $(OBJS)
	make -C MLX42 clean
	make -C include clean

fclean:
	@rm -f $(OBJS) $(NAME) $(BONUS_OBJS)
	make -C MLX42 fclean
	make -C include fclean

re: fclean all

.PHONY: all clean fclean re bonus