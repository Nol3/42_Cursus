TARGET = $(BIN_DIR)/pipex

FILES = pipex.c \
		utils.c

BIN_DIR = ./bin
LIBFT_DIR = ./libft
LIBFT_INC = $(LIBFT_DIR)/inc
LIBFT = $(LIBFT_DIR)/bin/libft.a

OBJS = $(addprefix $(OBJ_DIR)/,$(FILES:%.c=%.o))

INC_DIR = ./inc
OBJ_DIR = ./obj
SRC_DIR = ./src
INCLUDES = -I$(INC_DIR) -I$(LIBFT_INC)
CFLAGS =  -Wall -Wextra -Werror


$(TARGET): $(OBJS) $(LIBFT)
	mkdir -p $(BIN_DIR)
	gcc $(CFLAGS) $(INCLUDES) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	gcc $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

.PHONY: all clean fclean re

all: $(LIBFT) $(TARGET)

clean:
	@if [ -d $(OBJ_DIR) ]; then \
		rm -r $(OBJ_DIR); \
	fi
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@if [ -d $(BIN_DIR) ]; then \
		rm -r $(BIN_DIR); \
	fi
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all