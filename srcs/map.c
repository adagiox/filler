/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 10:38:55 by erintala          #+#    #+#             */
/*   Updated: 2017/10/15 10:38:57 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int		update_map(t_filler *filler, t_player *player)
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

int		init_mid(t_filler *filler, int i, int j)
{
	int y;
	int x;

	y = filler->height / 2 - 1;
	x = filler->width / 2 - 1;
	while (y > 0 && x > 0)
	{
		i = y;
		while (i < filler->height - y)
		{
			j = x;
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

void	checker(t_filler *filler)
{
	if (filler->start_row >= filler->height / 2)
		start_bot(filler);
	else
		start_top(filler);
}

void	start_bot(t_filler *filler)
{
	int row;
	int col;

	row = 0;
	while (row < filler->height)
	{
		col = 0;
		while (col < filler->width)
		{
			if (row == filler->start_row || row == 2 || col == 0 ||
				col == filler->width - 2 || col == filler->width / 2)
			{
				if (filler->map[row][col] != '#')
					filler->map[row][col] = '~';
			}
			col++;
		}
		row++;
	}
}

void	start_top(t_filler *filler)
{
	int row;
	int col;

	row = 0;
	while (row < filler->height)
	{
		col = 0;
		while (col < filler->width)
		{
			if (row == filler->start_row || row == filler->height - 2 ||
				col == 0 || col == filler->width - 2 ||
				col == filler->width / 2)
			{
				if (filler->map[row][col] != '#')
					filler->map[row][col] = '~';
			}
			col++;
		}
		row++;
	}
}
