NAME = filler

FLAGS = -Wall -Werror -Wextra

FILES = filler.c map.c setup.c piece.c place.c read.c print.c strategy.c

SRC = $(addprefix srcs/, $(FILES))

all: $(NAME)
	
$(NAME):
	make -C ./libft
	gcc $(FLAGS) $(SRC) -L./libft -lft -o $(NAME)

test: re
	./filler_vm -p1 ./carli.filler -p2 ./$(NAME) -f map00

clean:

fclean:
	rm -rf $(NAME)

re: fclean all