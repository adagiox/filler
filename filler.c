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
			map[i][j] = '1';
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
	init_mid(filler);
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

// int update_path(t_filler *filler)
// {

// }

int path_mid(int fd1, t_filler *filler)
{
	int y;
	int x;
	int ydir;
	int xdir;
	for (int i = 0; i < filler->height; i++)
	{
		for (int j = 0; j < filler->width; j++)
		{
			if (filler->map[i][j] == '#')
			{
				x = j;
				y = i;
				break ;
			}
		}
	}
	if (x > filler->width / 2)
		xdir = -1;
	else 
		xdir = 1;
	if (y > filler->height / 2)
		ydir = -1;
	else 
		ydir = 1;
	while (x != filler->width / 2 || y != filler->height / 2)
	{
		if (x != filler->width / 2)
			x += xdir;
		if (y != filler->height / 2)
			y += ydir;
		filler->map[y][x] = '~';
	}
	for (int i = 0; i < filler->height; i++)
	{
		for (int j = 0; j < filler->width; j++)
		{
			 if (i == filler->height / 2 || j == filler->width / 2)
			 	filler->map[i][j] = '~';
		}
	}
	return (1);
}

int init_mid(t_filler *filler)
{
	int y = filler->height / 2 - 1;
	int x = filler->width / 2 - 1;
	while (y > 0 && x > 0)
	{
		for (int i = y; i < filler->height - y; i++)
		{
			for (int j = x; j < filler->width - x; j++)
			{
				 filler->map[i][j] = filler->map[i][j] + 1;
			}
		}
		if (y > 0)
			y--;
		if (x > 0)
			x--;
	}
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
				filler->map[i][j] = '#';
			else if (filler->board[i][j] == player->opp_char)
				filler->map[i][j] = '$';
			else if (filler->board[i][j] == player->opp_char - 32)
				filler->map[i][j] = '+';
		}
	}
	return (1);
}

int set_piece_w(t_piece *piece)
{
	for (int i = 0; i < piece->width; i++)
	{
		for (int j = 0; j < piece->height; j++)
		{
			if (piece->piece[j][i] == '*')
				return (i);
		}
	}
	return (0);
}

int set_piece_h(t_piece *piece)
{
	for (int i = 0; i < piece->height; i++)
	{
		for (int j = 0; j < piece->width; j++)
		{
			if (piece->piece[i][j] == '*')
				return (i);
		}
	}
	return (0);
}

t_piece *set_offset(int fd1, t_piece *piece)
{
	print_piece(fd1, piece);
	piece->w_offset = set_piece_w(piece);
	piece->h_offset = set_piece_h(piece);
	return (piece);
}

t_piece *init_piece(int fd1, char **line)
{
	t_piece *piece;
	char *p;

	piece = (t_piece *)malloc(sizeof(piece));
	piece->w_offset = 0;
	piece->h_offset = 0;
	*line = *line + 6;
	piece->height = ft_atoi(*line);
	piece->width = ft_atoi(*line + ft_countdigits(piece->height) + 1);
	dprintf(fd1, "h: %i w: %i\n", piece->height, piece->width);
	piece->piece = (char **)malloc(sizeof(char *) * piece->height);
	ft_memset(piece->piece, '\0', piece->height);
	for (int i = 0; i < piece->height; i++)
	{
		get_next_line(0, line);
		p = ft_strnew(piece->width + 1);
		// ft_memset(p[i], '\0', piece->width + 1);
		for (int j = 0; j < piece->width + 1; j++)
			p[j] = (*line)[j];
		// p[i][piece->width] = '\0';
		piece->piece[i] = p;
	}
	piece = set_offset(fd1, piece);
	print_piece(fd1, piece);
	//dprintf(fd1, "offset: h: %i w: %i\n", piece->h_offset, piece->w_offset);
	return (piece);
}

int check_place(int fd1, t_filler *filler, t_piece *piece, int y, int x)
{
	int score;
	int num_char;
	int b_col;

	b_col = x;
	score = 0;
	num_char = 0;
	for (int i = piece->h_offset; i < piece->height; i++)
	{
		x = b_col;
		for (int j = piece->w_offset; j < piece->width; j++)
		{		
			//dprintf(fd1, "y:%i, x:%i\n", y, x);
			if (piece->piece[i][j] == '*')
			{
				if (x >= filler->width || y >= filler->height)
					return (-1);
				if (filler->map[y][x] == '+' || filler->map[y][x] == '$')
					return (-1);
				if (filler->map[y][x] == '#')
					num_char++;
				score += filler->map[y][x];
			}
			x++;
		}
		y++;
	}
	//dprintf(fd1, "\n");
	if (num_char == 1)
		return (score);
	return (-1);
}

int place_piece(int fd1, t_filler *filler, t_piece *piece)
{
	int max;
	int score;
	int x;
	int y;

	max = 0;
	score = 0;
	x = 0;
	y = 0;
	for (int i = 0; i < filler->height; i++)
	{
		for (int j = 0; j < filler->width; j++)
		{
			if ((score = check_place(fd1, filler, piece, i, j)) >= max)
			{
				x = j;
				y = i;
				max = score;
			}
			//dprintf(fd1, "score: %i x: %i y: %i\n", score, j, i);
		}
	}
	dprintf(fd1, "max: %i\n", max);
	if (max > 0)
	{
		print_piece(fd1, piece);
		dprintf(fd1, "offset: h: %i w: %i\n", piece->h_offset, piece->w_offset);
		dprintf(fd1, "place: h: %i w: %i\n", y - piece->h_offset, x - piece->w_offset);

		ft_printf("%i %i\n", y - piece->h_offset, x - piece->w_offset);
		return (1);
	}
	return (-1);
}

int next_line()
{
	int ret;
	char *line;
	t_player *player;
	t_filler *filler;

	ret = 1;
	int fd1 = open("testing.txt", O_CREAT | O_APPEND | O_RDWR);
	while (ret != -1)
	{
		ret = get_next_line(0, &line);
		dprintf(fd1, "ret: %i\n", ret);
		if (ft_strstr(line, "Plateau ") && ret > 0)
			ret = get_next_line(0, &line);
		if (ft_strstr(line, "  012") && ret > 0)
		{
			update_board(filler, player, &line);
			update_map(filler, player);
			print_filler(fd1, filler);
			print_map(fd1, filler);
		}
		else if (ft_strstr(line, "Piece ") && ret > 0)
		{
			//dprintf(fd1, "line: %s\n", line);
			player->piece = init_piece(fd1, &line);
			//dprintf(fd1, "line: %s\n", line);
			dprintf(fd1, "offset: h: %i w: %i\n", player->piece->h_offset, player->piece->w_offset);
			place_piece(fd1, filler, player->piece);
		}
		else if (ft_strstr(line, "exec") && ret > 0)
		{
			//dprintf(fd1, "line: %s\n", line);
			player = init_player(line);
			ret = get_next_line(0, &line);
			filler = init_filler(line);
			print_player(fd1, player);
			print_filler(fd1, filler);
			print_map(fd1, filler);
			dprintf(fd1, "SETUP COMPLETE\n\n");
			ret = get_next_line(0, &line);
			update_board(filler, player, &line);
			update_map(filler, player);
			print_filler(fd1, filler);
			print_map(fd1, filler);
			path_mid(fd1, filler);
			print_filler(fd1, filler);
			print_map(fd1, filler);
		}
		// need to make sure -1 is returned 
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