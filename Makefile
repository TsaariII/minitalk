NAME_C = client

NAME_S = server

SRC_DIR = sources/

SRC_C = $(SRC_DIR)client.c\
		$(SRC_DIR)utils.c
SRC_S = $(SRC_DIR)server.c\
		$(SRC_DIR)utils.c

FLAGS = -Wall -Werror -Wextra -g

LIBFT = ./libft/libft.a

OBJ_DIR = objects/

OBJS_C = $(OBJ_DIR)client.o \
		$(OBJ_DIR)utils_client.o

OBJS_S = $(OBJ_DIR)server.o \
		$(OBJ_DIR)utils_server.o

LIBFT_DIR = ./libft

MAKEFLAGS += --no-print-directory

all: $(LIBFT) $(NAME_C) $(NAME_S)

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)client.o: $(SRC_DIR)client.c | $(OBJ_DIR)
		@cc $(FLAGS) -c $< -o $@

$(OBJ_DIR)server.o: $(SRC_DIR)server.c | $(OBJ_DIR)
		@cc $(FLAGS) -c $< -o $@

$(OBJ_DIR)utils_server.o: $(SRC_DIR)utils.c | $(OBJ_DIR)
		@cc $(FLAGS) -c $< -o $@

$(OBJ_DIR)utils_client.o: $(SRC_DIR)utils.c | $(OBJ_DIR)
		@cc $(FLAGS) -c $< -o $@

$(LIBFT):
		@make -C $(LIBFT_DIR) all
		@echo "\n\033[0;32mLibft ready\033[0m\n"

$(NAME_C): $(OBJS_C) $(LIBFT)
		@cc $(OBJS_C) $(LIBFT) -o $(NAME_C) > /dev/null
		@echo "\n\033[0;32mClient ready!\033[0m\n"

$(NAME_S): $(OBJS_S) $(LIBFT)
		@cc $(OBJS_S) $(LIBFT) -o $(NAME_S) > /dev/null
		@echo "\n\033[0;32mServer is up and running!\033[0m\n"

clean:
		@rm -f $(OBJS_C) $(OBJS_S)
		@rm -rf $(OBJ_DIR)
		@make -C $(LIBFT_DIR) clean

fclean:
		@rm -f $(NAME_C) $(NAME_S)
		@rm -f $(OBJS_C) $(OBJS_S)
		@make -C $(LIBFT_DIR) fclean
		@echo "\n\033[0;31mAll is gone\033[0m\n"

re: fclean all

.PHONY: all clean fclean re libft
