#include "filler.h"

// void print_player(int fd1, t_player *player)
// {
// 	dprintf(fd1, "player_init: %u, %c\n", player->player, player->player_char);
// 	dprintf(fd1, "\n");
// }

// void print_filler(int fd1, t_filler *filler)
// {
// 	for(int i = 0; i < filler->height; i++)
// 		dprintf(fd1, "%s\n", filler->board[i]);
// 	dprintf(fd1, "\n");
// }

// void print_map(int fd1, t_filler *filler)
// {
// 	for (int i = 0; i < filler->height; i++)
// 		dprintf(fd1, "%s\n", filler->map[i]);
// 	dprintf(fd1, "\n");
// }

// void print_piece(int fd1, t_player *player)
// {
// 	dprintf(fd1, "Print piece:\n");
// 	for(int i = 0; i < player->p_rows; i++)
// 		dprintf(fd1, "piece: %s\n", player->piece[i]);
// 	dprintf(fd1, "\n");
// }

char **init_map(t_filler *filler)
{
	char **map;
	int i;

	i = 0;
	map = (char **)malloc(sizeof(char *) * filler->height);
	while (i < filler->height)
	{
		map[i] = ft_strnew(filler->width + 1);
		for (int j = 0; j < filler->width; j++)
			map[i][j] = '1';
		map[i][filler->width] = '\0';
		i++;
	}
	return (map);
}

t_filler *init_filler(char *line)
{
	t_filler *filler;
	char **h;
	int i;
	int j;

	i = 0;
	j = 0;
	filler = (t_filler *)malloc(sizeof(t_filler));
	line += 8;
	filler->height = ft_atoi(line);
	line += ft_countdigits(filler->height) + 1;
	filler->width = ft_atoi(line);
	h = (char **)malloc(sizeof(char *) * filler->height);
	while (i < filler->height)
	{
		h[i] = ft_strnew(filler->width + 1);
		while (j < filler->width)
		{
			h[i][j] = '.';
			j++;
		}
		h[i][filler->width] = '\0';
		i++;
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

	player = ft_memalloc(sizeof(t_player));
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

int path_mid(t_filler *filler)
{
	int y;
	int x;

	for (int i = 0; i < filler->height; i++)
	{
		for (int j = 0; j < filler->width; j++)
		{
			if (filler->map[i][j] == '#')
			{
				x = j;
				y = i;
				filler->start_row = y;
				filler->start_col = x;
				break ;
			}
		}
	}
	checker(filler);
	return (1);
}

void	checker(t_filler *filler)
{
	int row;
	int col;

	row = 0;
	while (row < filler->height)
	{
		col = 0;
		while (col < filler->width)
		{
			if ((col == filler->start_col && row <= filler->start_row) ||
				row == 2)
			{
				if (filler->map[row][col] != '#')
					filler->map[row][col] = '~';
			}
			col++;
		}
		row++;
	}
}

int init_mid(t_filler *filler)
{
	int i;
	int j;
	int y;
	int x;

	i = 0;
	y = filler->height / 2 - 1;
	x = filler->width / 2 - 1;
	while (y > 0 && x > 0)
	{
		while (i < filler->height - y)
		{
			j = 0;
			while (j < filler->width - x)
			{
				 filler->map[i][j] = filler->map[i][j] + 1;
				 j++;
			}
			i++;
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
	int i;
	int j;

	i = 0;
	while (i < filler->height)
	{
		j = 0;
		while (j < filler->width)
		{
			if (filler->board[i][j] == player->player_char ||
				filler->board[i][j] == player->player_char - 32)
				filler->map[i][j] = '#';
			else if (filler->board[i][j] == player->opp_char)
				filler->map[i][j] = '$';
			else if (filler->board[i][j] == player->opp_char - 32)
				filler->map[i][j] = '+';
			j++;
		}
		i++;
	}
	return (1);
}

void	set_piece_col(t_player *player)
{
	int i;
	int j;

	i = 0;
	while (i < player->p_cols)
	{
		j = 0;
		while (j < player->p_rows)
		{
			if (player->piece[j][i] == '*')
			{
				player->col_offset = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	set_piece_row(t_player *player)
{
	int row;
	int col;

	row = 0;
	while (row < player->p_rows)
	{
		col = 0;
		while (col < player->p_cols)
		{
			if (player->piece[row][col] == '*')
			{
				player->row_offset = row;
				return ;
			}
			col++;
		}
		row++;
	}
}

void	set_offset(t_player *player)
{
	set_piece_col(player);
	set_piece_row(player);
}

void	get_piece(char *line, t_player *player)
{
	int	row;
	int	i;
	
	row = 0;
	while(row < player->p_rows)
	{
		i = 0;
		ft_strdel(&line);
		get_next_line(0, &line);
		while (line[i])
		{
			player->piece[row][i] = line[i];
			i++;
		}
		row++;
	}
}

void	init_piece(char **line, t_player *player)
{
	int	row;
	int	i;

	i = 6;
	row = 0;
	player->col_offset = 0;
	player->row_offset = 0;
	player->p_rows = ft_atoi(&line[0][i]);
	i += ft_countdigits(player->p_rows) + 1;
	player->p_cols = ft_atoi(&line[0][i]);
	player->piece = malloc(sizeof(char *) * player->p_rows);
	ft_bzero(player->piece, player->p_rows);
	while (row < player->p_rows)
	{
		player->piece[row] = ft_memalloc(sizeof(char) * player->p_cols);
		row++;
	}
	get_piece(*line, player);
	set_offset(player);
}

int free_piece(t_player *player)
{
	for (int i = 0; i < player->p_rows; i++)
		free(player->piece[i]);
	free(player->piece);
	return (1);
}

int check_place(t_filler *filler, t_player *player, int y, int x)
{
	int score;
	int num_char;
	int b_col;

	b_col = x;
	score = 0;
	num_char = 0;
	for (int i = player->row_offset; i < player->p_rows; i++)
	{
		x = b_col;
		for (int j = player->col_offset; j < player->p_cols; j++)
		{		
			if (player->piece[i][j] == '*')
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
	if (num_char == 1)
		return (score);
	return (-1);
}

int place_piece(t_filler *filler, t_player *player)
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
			if ((score = check_place(filler, player, i, j)) >= max)
			{
				x = j;
				y = i;
				max = score;
			}
		}
	}
	if (max > 0)
	{
		ft_printf("%i %i\n", y - player->row_offset, x - player->col_offset);
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
	while (ret > 0)
	{
		ret = get_next_line(0, &line);
		if (ft_strstr(line, "Plateau ") && ret > 0)
			ret = get_next_line(0, &line);
		if (ft_strstr(line, "  012") && ret > 0)
		{
			update_board(filler, player, &line);
			update_map(filler, player);
		}
		else if (ft_strstr(line, "Piece ") && ret > 0)
		{
			init_piece(&line, player);
			if (place_piece(filler, player) == -1)
			{
				free_piece(player);
				ft_printf("-1 -1\n");
				break ;
			}
			free_piece(player);
		}
		else if (ft_strstr(line, "exec") && ret > 0)
		{
			player = init_player(line);
			ret = get_next_line(0, &line);
			filler = init_filler(line);
			ret = get_next_line(0, &line);
			update_board(filler, player, &line);
			update_map(filler, player);
			path_mid(filler);
		}
	}
	return (0);
}

int main()
{
	int done;

	done = 1;
	while (done > 0)
		done = next_line();

	return (0);
}