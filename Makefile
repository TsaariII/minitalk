NAME = minitalk

SRC = client.c\
	server.c

FLAGS = -Wall -Werror -Wextra -g

LIBFT = $(LIBFT_DIR)/libft.a

LIBFT_DIR = ./libft

HEADS = -I$(LIBFT_DIR)

MAKEFLAGS += --no-print-directory

all: $(LIBFT) $(NAME)

$(LIBFT):
		@$(MAKE) -C $(LIBFT_DIR)

OBJS = $(SRC:.c=.o)

%.o: %.c
		@cc $(FLAGS) -c $< -o $@ $(HEADS)

$(NAME): $(OBJS)
		@echo "\n\033[0;32mLibft ready\033[0m\n"
		@cc $(OBJS) $(LIBFT) -o $(NAME) > /dev/null
		@echo "\n\033[0;32mTime to communicate!\033[0m\n"

clean:
		@rm -f $(OBJS)
		@$(MAKE) -C $(LIBFT_DIR) clean

fclean:
		@rm -f $(NAME)
		@rm -f $(OBJS)
		@$(MAKE) -C $(LIBFT_DIR) fclean
		@rm -f fdf.a
		@echo "\n\033[0;31mAll is gone\033[0m\n"

re: fclean all

.PHONY: all clean fclean re libft
