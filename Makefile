NAME = filler

FLAGS = -Wall -Werror -Wextra

FILES = filler.c map.c setup.c piece.c place.c read.c print.c strategy.c

SRC = $(addprefix srcs/, $(FILES))

all: $(NAME)
	
$(NAME):
	make -C ./libft
	gcc $(FLAGS) $(SRC) -L./libft -lft -o $(NAME)

clean:

fclean:
	rm -rf $(NAME)

re: fclean all