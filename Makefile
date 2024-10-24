NAME_C = client

NAME_S = server

SRC_DIR = sources/

SRC_C = $(SRC_DIR)client.c
SRC_S = $(SRC_DIR)server.c

FLAGS = -Wall -Werror -Wextra -g

LIBFT = ./libft/libft.a

OBJ_DIR = objects/

OBJS_C = $(OBJ_DIR)client.o

OBJS_S = $(OBJ_DIR)server.o

LIBFT_DIR = ./libft

MAKEFLAGS += --no-print-directory

all: libft $(NAME_C) $(NAME_S)

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)client.o: $(SRC_C) | $(OBJ_DIR)
		@cc $(FLAGS) -c $< -o $@

$(OBJ_DIR)server.o: $(SRC_S) | $(OBJ_DIR)
		@cc $(FLAGS) -c $< -o $@

libft:
		@make -C $(LIBFT_DIR)
		@echo "\n\033[0;32mLibft ready\033[0m\n"

$(NAME_C): $(OBJS_C)
		@cc $(OBJS_C) $(LIBFT) -o $(NAME_C) > /dev/null
		@echo "\n\033[0;32mClient ready!\033[0m\n"

$(NAME_S): $(OBJS_S)
		@cc $(OBJS_S) $(LIBFT) -o $(NAME_S) > /dev/null
		@echo "\n\033[0;32mServer is up and running!\033[0m\n"

clean:
		@rm -f $(OBJS_C) $(OBJS_S)
		@make -C $(LIBFT_DIR) clean

fclean:
		@rm -f $(NAME_C) $(NAME_S)
		@rm -f $(OBJS_C) $(OBJS_S)
		@make -C $(LIBFT_DIR) fclean
		@echo "\n\033[0;31mAll is gone\033[0m\n"

re: fclean all

.PHONY: all clean fclean re libft
