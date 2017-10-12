all:
	make -C ./libft
	gcc filler.c -L./libft -lft

debug:
	make -C ./libft
	gcc filler.c -L./libft -lft	-g


test: all
	./filler_vm -p1 ./superjeannot.filler -p2 ./a.out -f map01

test2: all
	rm -rf testing.txt
	./filler_vm -p2 ./abanlin.filler -p1 ./a.out -f map02
	chmod +wrx testing.txt

# rm -rf testing.txt
# ./filler_vm -p1 ./abanlin.filler -p2 ./a.out -f map00
# chmod +wrx testing.txt