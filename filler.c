#include "filler.h"

void print_player(t_player *player)
{
	
}

t_player *init_player(char *line)
{
	t_player *player;
	char *p;


	player = (t_player*)malloc(sizeof(t_player));
	p = ft_strstr(line, " p");
	player->player = *(p + 2) - 48;
	player->player_char = ' ';
	
	return(player);
}

int next_line()
{
	int ret;
	char *line;
	t_player *player;

	ret = 1;
	
	while (ret > 0)
	{
		//ft_printf("while:\n");
		ret = get_next_line(0, &line);
		int fd1 = open("testret.txt", O_CREAT | O_APPEND | O_RDWR);
		dprintf(fd1, "line1: %s\n", line);
		// if (line)
		// {
		// int fd = open("testret1.txt", O_RDWR);
		// dprintf(fd, "line: %s\n", line);
		// 	return 0;
		// }
		
		if (ft_strstr(line, "exec"))
		{
			dprintf(fd1, "line2: %s\n", line);
			player = init_player(line);
			//print_player(player);
		}
		// else if (ft_strstr(line, "Plateau "))
		// {}
		// else if (ft_strstr(line, ""))
		
		close(fd1);
		ret = 0;
	}
	return (ret);
}

int main()
{
	int done;

	//usleep(100);
	done = 1;
	while (done > 0)
		done = next_line();
	//ft_printf("Hello, World!\n");
	return (done);
}