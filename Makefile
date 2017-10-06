all:
	make -C ./libft
	gcc filler.c -L./libft -lft