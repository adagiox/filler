/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 11:06:17 by erintala          #+#    #+#             */
/*   Updated: 2017/10/15 11:06:23 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include <stdio.h>
# include <stdlib.h>
# include "../libft/includes/libft.h"

typedef struct	s_filler
{
	int		width;
	int		height;
	char	**board;
	char	**map;
	int		start_row;
	int		start_col;
}				t_filler;

typedef struct	s_player
{
	int		player;
	char	player_char;
	char	opp_char;
	int		p_cols;
	int		p_rows;
	int		col_offset;
	int		row_offset;
	char	**piece;
	int		score;
	int		num_char;
	int		b_col;
	int		max;
}				t_player;

t_player		*init_player(char *line);
t_filler		*init_filler(char *line);
int				filler(void);
int				update_board(t_filler *filler, t_player *player, char **line);
int				line_piece(t_player *player, t_filler *filler, char *line);
int				line_board(t_player *player, t_filler *filler, char *line);
void			print_map(t_filler *filler);
int				update_map(t_filler *filler, t_player *player);
char			**init_map(t_filler *filler);
t_filler		*set_filler(t_filler *filler, char *line);
int				init_mid(t_filler *filler, int i, int j);
void			path_mid(t_filler *filler);
void			get_piece(char *line, t_player *player);
int				init_piece(char **line, t_player *player);
int				free_piece(t_player *player);
int				print_place(int y, int x, t_player *player);
int				place_piece(t_filler *filler, t_player *player);
int				check_valid(t_player *player, t_filler *filler, int x, int y);
int				check_place(t_filler *filler, t_player *player, int y, int x);
void			set_piece_col(t_player *player);
void			set_piece_row(t_player *player);
void			print_piece(t_player *player);
void			start_bot_right(t_filler *filler);
void			start_bot_left(t_filler *filler);
void			start_top_right(t_filler *filler);
void			start_top_left(t_filler *filler);
void			strategy(t_filler *filler);

#endif
