/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 10:39:14 by erintala          #+#    #+#             */
/*   Updated: 2017/10/15 10:39:16 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int	print_place(int y, int x, t_player *player)
{
	if (player->max > 0)
	{
		ft_printf("%i %i\n", y - player->row_offset, x - player->col_offset);
		return (1);
	}
	else
		ft_printf("-1 -1\n");
	return (-1);
}

int	place_piece(t_filler *filler, t_player *player)
{
	int x;
	int y;
	int i;
	int j;

	player->max = 0;
	player->score = 0;
	x = 0;
	y = 0;
	i = -1;
	while (++i < filler->height && (j = -1))
	{
		while (++j < filler->width)
		{
			if ((player->score = check_place(filler, player, i, j))
				>= player->max)
			{
				x = j;
				y = i;
				player->max = player->score;
			}
		}
	}
	return (print_place(y, x, player));
}

int	check_valid(t_player *player, t_filler *filler, int x, int y)
{
	if (x >= filler->width || y >= filler->height)
		return (-1);
	if (filler->map[y][x] == '+' || filler->map[y][x] == '$')
		return (-1);
	if (filler->map[y][x] == '#')
		player->num_char++;
	player->score += filler->map[y][x];
	return (1);
}

int	set_place(t_player *player, int x)
{
	player->b_col = x;
	player->score = 0;
	player->num_char = 0;
	return (player->row_offset);
}

int	check_place(t_filler *filler, t_player *player, int y, int x)
{
	int i;
	int j;

	i = set_place(player, x);
	while (i < player->p_rows)
	{
		x = player->b_col;
		j = player->col_offset;
		while (j < player->p_cols)
		{
			if (player->piece[i][j] == '*')
			{
				if (check_valid(player, filler, x, y) == -1)
					return (-1);
			}
			x++;
			j++;
		}
		y++;
		i++;
	}
	if (player->num_char == 1)
		return (player->score);
	return (-1);
}
