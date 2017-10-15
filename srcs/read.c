/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 10:39:38 by erintala          #+#    #+#             */
/*   Updated: 2017/10/15 10:39:39 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int	update_board(t_filler *filler, char **line)
{
	char	*l;
	int		ret;
	int		i;
	int		j;

	ret = 0;
	i = 0;
	while (i < filler->height)
	{
		j = 0;
		ret = get_next_line(0, line);
		l = *line + 4;
		while (j < filler->width)
		{
			filler->board[i][j] = *l;
			l++;
			j++;
		}
		i++;
	}
	return (ret);
}

int	line_piece(t_player *player, t_filler *filler, char *line)
{
	init_piece(&line, player);
	if (place_piece(filler, player) == -1)
	{
		ft_printf("-1 -1\n");
		free_piece(player);
		return (-1);
	}
	free_piece(player);
	return (1);
}

int	line_board(t_player *player, t_filler *filler, char *line)
{
	update_board(filler, &line);
	update_map(filler, player);
	return (1);
}

int	next_turn(t_player *player, t_filler *filler, char **line, int ret)
{
	if ((ret = get_next_line(0, line)) && ft_strstr(*line, "Plateau "))
		ret = get_next_line(0, line);
	if (ft_strstr(*line, "  012") && ret > 0)
		line_board(player, filler, *line);
	else if (ft_strstr(*line, "Piece ") && init_piece(line, player) && ret > 0)
	{
		if (place_piece(filler, player) == -1)
			return (-1);
		free_piece(player);
	}
	return (ret);
}

int	filler(void)
{
	int			ret;
	char		*line;
	t_player	*player;
	t_filler	*filler;

	ret = get_next_line(0, &line);
	if (ft_strstr(line, "exec") && ret > 0)
	{
		player = init_player(line);
		ret = get_next_line(0, &line);
		filler = init_filler(line);
		ret = get_next_line(0, &line);
		line_board(player, filler, line);
		path_mid(filler);
	}
	ret = 1;
	while (ret > 0)
		ret = next_turn(player, filler, &line, ret);
	return (0);
}
