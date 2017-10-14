#include "../includes/filler.h"

int free_piece(t_player *player)
{
	int i;
	
	i = 0;
	while (i < player->p_rows)
	{
		free(player->piece[i]);
		i++;
	}
	free(player->piece);
	return (1);
}

int	init_piece(char **line, t_player *player)
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
	set_piece_col(player);
	set_piece_row(player);
	return (1);
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