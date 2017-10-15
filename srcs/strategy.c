/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 11:43:22 by erintala          #+#    #+#             */
/*   Updated: 2017/10/15 11:43:27 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void	start_bot_right(t_filler *filler)
{
	int row;
	int col;

	row = -1;
	while (++row < filler->height)
	{
		col = -1;
		while (++col < filler->width)
		{
			if ((row == filler->start_row || col == filler->start_col) &&
				col <= filler->start_col && row <= filler->start_row &&
				filler->map[row][col] != '#')
				filler->map[row][col] = '~';
		}
	}
}

void	start_bot_left(t_filler *filler)
{
	int row;
	int col;

	row = -1;
	while (++row < filler->height)
	{
		col = -1;
		while (++col < filler->width)
		{
			if ((row == filler->start_row || col == filler->start_col) &&
				col >= filler->start_col && row <= filler->start_row &&
				filler->map[row][col] != '#')
				filler->map[row][col] = '~';
		}
	}
}

void	start_top_right(t_filler *filler)
{
	int row;
	int col;

	row = -1;
	while (++row < filler->height)
	{
		col = -1;
		while (++col < filler->width)
		{
			if ((row == filler->start_row || col == filler->start_col) &&
				col <= filler->start_col && row >= filler->start_row &&
				filler->map[row][col] != '#')
				filler->map[row][col] = '~';
		}
	}
}

void	start_top_left(t_filler *filler)
{
	int row;
	int col;

	row = -1;
	while (++row < filler->height)
	{
		col = -1;
		while (++col < filler->width)
		{
			if ((row == filler->start_row || col == filler->start_col) &&
				col >= filler->start_col && row >= filler->start_row &&
				filler->map[row][col] != '#')
				filler->map[row][col] = '~';
		}
	}
}
