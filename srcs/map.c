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

	y = filler->height / 2;
	x = filler->width / 2;
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

void	strategy(t_filler *filler)
{
	if (filler->start_row >= filler->height / 2)
	{
		if (filler->start_col >= filler->width / 2)
			start_bot_right(filler);
		else
			start_bot_left(filler);
	}
	else
	{
		if (filler->start_col >= filler->width / 2)
			start_top_right(filler);
		else
			start_top_left(filler);
	}
}
