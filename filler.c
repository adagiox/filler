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
	int fd = open("test.txt", O_CREAT | O_RDWR);
	dprintf(fd, "line: %s", line);
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
		if (ft_strstr(line, "exec"))
		{
			player = init_player(line);
			//print_player(player);
		}
		// else if (ft_strstr(line, "Plateau "))
		// {}
		// else if (ft_strstr(line, ""))
		
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