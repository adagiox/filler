#include "../includes/filler.h"

int print_place(int y, int x, int max, t_player *player)
{
	if (max > 0)
	{
		ft_printf("%i %i\n", y - player->row_offset, x - player->col_offset);
		return (1);
	}
	else
		ft_printf("-1 -1\n");
	return (-1);
}

int place_piece(t_filler *filler, t_player *player)
{
	int max;
	int score;
	int x;
	int y;
	int i;
	int j;

	max = 0;
	x = 0;
	y = 0;
	i = -1;
	while (++i < filler->height && (j = -1))
	{
		while (++j < filler->width)
		{
			if ((score = check_place(filler, player, i, j)) >= max)
			{
				x = j;
				y = i;
				max = score;
			}
		}
	}
	return (print_place(y, x, max, player));
}

int check_place(t_filler *filler, t_player *player, int y, int x)
{
	int score;
	int num_char;
	int b_col;
	int i;
	int j;

	b_col = x;
	score = 0;
	num_char = 0;
	i = player->row_offset;
	while (i < player->p_rows)
	{
		x = b_col;
		j = player->col_offset;
		while (j < player->p_cols)
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
			j++;
		}
		y++;
		i++;
	}
	if (num_char == 1)
		return (score);
	return (-1);
}