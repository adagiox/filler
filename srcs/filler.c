#include "../includes/filler.h"

void print_map(t_filler *filler)
{
	int fd1 = open("testing.txt", O_CREAT | O_RDWR);
	for (int i = 0; i < filler->height; i++)
		dprintf(fd1, "%s\n", filler->map[i]);
	dprintf(fd1, "\n");
	close(fd1);
}

int main()
{
	int done;

	done = 1;
	while (done > 0)
		done = filler();

	return (0);
}