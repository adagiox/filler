/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 10:39:49 by erintala          #+#    #+#             */
/*   Updated: 2017/10/15 10:39:51 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

char		**init_map(t_filler *filler)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	map = (char **)malloc(sizeof(char *) * filler->height);
	while (i < filler->height)
	{
		j = 0;
		map[i] = ft_strnew(filler->width + 1);
		while (j < filler->width)
		{
			map[i][j] = '1';
			j++;
		}
		map[i][filler->width] = '\0';
		i++;
	}
	return (map);
}

t_filler	*set_filler(t_filler *filler, char *line)
{
	filler = (t_filler *)malloc(sizeof(t_filler));
	line += 8;
	filler->height = ft_atoi(line);
	line += ft_countdigits(filler->height) + 1;
	filler->width = ft_atoi(line);
	return (filler);
}

t_filler	*init_filler(char *line)
{
	t_filler	*filler;
	char		**h;
	int			i;
	int			j;

	i = 0;
	j = 0;
	filler = set_filler(filler, line);
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
	init_mid(filler, i, j);
	return (filler);
}

t_player	*init_player(char *line)
{
	t_player	*player;
	char		*p;

	player = ft_memalloc(sizeof(t_player));
	player->num_char = 0;
	player->score = 0;
	player->b_col = 0;
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
	return (player);
}

void		path_mid(t_filler *filler)
{
	int y;
	int x;
	int i;
	int j;

	i = 0;
	while (i < filler->height)
	{
		j = 0;
		while (j < filler->width)
		{
			if (filler->map[i][j] == '#')
			{
				x = j;
				y = i;
				filler->start_row = y;
				filler->start_col = x;
				break ;
			}
			j++;
		}
		i++;
	}
	strategy(filler);
}
