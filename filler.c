#include "filler.h"

void print_player(int fd1, t_player *player)
{
	dprintf(fd1, "player_init: %u, %c\n", player->player, player->player_char);
	dprintf(fd1, "\n");
}

void print_filler(int fd1, t_filler *filler)
{
	for(int i = 0; i < filler->height; i++)
		dprintf(fd1, "%s\n", filler->board[i]);
	dprintf(fd1, "\n");
}

void print_map(int fd1, t_filler *filler)
{
	for (int i = 0; i < filler->height; i++)
		dprintf(fd1, "%s\n", filler->map[i]);
	dprintf(fd1, "\n");
}

void print_piece(int fd1, t_piece *piece)
{
	for(int i = 0; i < piece->height; i++)
		dprintf(fd1, "piece: %s\n", piece->piece[i]);
	dprintf(fd1, "\n");
}

char **init_map(t_filler *filler)
{
	char **map;

	map = (char **)malloc(sizeof(char *) * filler->height);
	for (int i = 0; i < filler->height; i++)
	{
		map[i] = ft_strnew(filler->width + 1);
		for (int j = 0; j < filler->width; j++)
			map[i][j] = ' ';
		map[i][filler->width] = '\0';
	}

	return (map);
}

t_filler *init_filler(char *line)
{
	t_filler *filler;
	char **h;

	filler = (t_filler *)malloc(sizeof(t_filler));
	line += 8;
	filler->height = ft_atoi(line);
	line += ft_countdigits(filler->height) + 1;
	filler->width = ft_atoi(line);
	h = (char **)malloc(sizeof(char *) * filler->height);
	for(int i = 0; i < filler->height; i++)
	{
		h[i] = ft_strnew(filler->width + 1);
		for (int j = 0; j < filler->width; j++)
			h[i][j] = '.';
		h[i][filler->width] = '\0';
	}
	filler->board = h;
	filler->map = init_map(filler);
	return(filler);
}

t_player *init_player(char *line)
{
	t_player *player;
	char *p;

	player = (t_player*)malloc(sizeof(t_player));
	p = ft_strstr(line, " p");
	player->player = *(p + 2) - 48;
	if (player->player == 1)
	{
		player->player_char = 'O';
		player->opp_char = 'X';
	}
	else
	{
		player->player_char = 'X';
		player->opp_char = 'O';
	}
	return(player);
}

int update_board(t_filler *filler, t_player *player, char **line)
{
	char *l;
	int ret;

	ret = 0;
	for (int i = 0; i < filler->height; i++)
	{
		ret = get_next_line(0, line);
		l = *line + 4;
		for (int j = 0; j < filler->width; j++)
		{
			filler->board[i][j] = *l;
			l++;
		}
	}
	return (ret);
}

int init_q1(t_filler *filler, t_player *player, int y, int x)
{
	int i = 0;
	int j = 0;
}

int init_q2(t_filler *filler, t_player *player, int y, int x)
{
	int i = 0;
	int j = 0;
}

int init_q3(t_filler *filler, t_player *player, int y, int x)
{
	int i = 0;
	int j = 0;
}

int init_q4(t_filler *filler, t_player *player, int y, int x)
{
	int i = 0;
	int j = 0;
}

int init_mid(t_filler *filler, t_player *player, int y, int x)
{
	if (y < filler->height / 2 && x < filler->width / 2)
		init_q1(filler, player, y, x);
	else if (y < filler->height / 2 && x > filler->width / 2)
		init_q2(filler, player, y, x);
	else if (y > filler->height / 2 && x > filler->width / 2)
		init_q4(filler, player, y, x);
	else if (y > filler->height / 2 && x < filler->width / 2)
		init_q3(filler, player, y, x);
	return (1);
}

int update_map(t_filler *filler, t_player *player)
{
	for (int i = 0; i < filler->height; i++)
	{
		for (int j = 0; j < filler->width; j++)
		{
			if (filler->board[i][j] == player->player_char ||
				filler->board[i][j] == player->player_char - 32)
				filler->map[i][j] = '2';
			else if (filler->board[i][j] == player->opp_char)
				filler->map[i][j] = '1';
			else if (filler->board[i][j] == player->opp_char - 32)
				filler->map[i][j] = '3';
		}
	}
	return (1);
}

// t_piece *reduce_piece(t_piece *piece)
// {

// }

t_piece *init_piece(int fd1, char **line)
{
	t_piece *piece;
	char **p;

	piece = (t_piece *)malloc(sizeof(piece));
	piece->w_offset = 0;
	piece->h_offset = 0;
	*line = *line + 6;
	piece->height = ft_atoi(*line);
	piece->width = ft_atoi(*line + ft_countdigits(piece->height) + 1);
	dprintf(fd1, "height: %i, width: %i\n", piece->height, piece->width);
	p = (char **)malloc(sizeof(char *) * piece->height);
	for (int i = 0; i < piece->height; i++)
	{
		get_next_line(0, line);
		dprintf(fd1, "line%i: %s\n", i + 1, *line);
		p[i] = ft_strnew(piece->width + 1);
		for (int j = 0; j < piece->width; j++)
			p[i][j] = (*line)[j];
		p[i][piece->width] = '\0';
		dprintf(fd1, "p%i: %s\n", i + 1, p[i]);
	}
	piece->piece = p;
	return (piece);
}

// int place_piece(t_player *player, t_filler *filler, t_piece *piece)
// {

// }

int next_line()
{
	int ret;
	char *line;
	t_player *player;
	t_filler *filler;

	ret = 1;
	int fd1 = open("testing.txt", O_CREAT | O_APPEND | O_RDWR);
	while (ret > 0)
	{
		ret = get_next_line(0, &line);
		if (ft_strstr(line, "Plateau ") && ret > 0)
			ret = get_next_line(0, &line);
		else if (ft_strstr(line, "  012") && ret > 0)
		{
			update_board(filler, player, &line);
			update_map(filler, player);
			print_filler(fd1, filler);
			print_map(fd1, filler);
		}
		else if (ft_strstr(line, "Piece ") && ret > 0)
		{
			dprintf(fd1, "line: %s\n", line);
			player->piece = init_piece(fd1, &line);
			dprintf(fd1, "line: %s\n", line);
			//place_piece(player, filler, piece);
			print_piece(fd1, player->piece);
		}
		else if (ft_strstr(line, "exec") && ret > 0)
		{
			dprintf(fd1, "line: %s\n", line);
			player = init_player(line);
			ret = get_next_line(0, &line);
			filler = init_filler(line);
			init_cross(filler, player);
			print_player(fd1, player);
			print_filler(fd1, filler);
			print_map(fd1, filler);
		}
		else 
			ret = -1;
		// make sure -1 is returned 
	}
	close(fd1);
	return (ret);
}

int main()
{
	int done;

	done = 1;
	while (done > 0)
		done = next_line();

	return (done);
}