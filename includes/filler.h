#include <stdio.h>
#include <stdlib.h>
#include "../libft/includes/libft.h"

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
}				t_player;

t_player	*init_player(char *line);
t_filler	*init_filler(char *line);
int			filler();
int			update_board(t_filler *filler, t_player *player, char **line);
int			line_player(t_player *player, t_filler *filler, char *line);
int			line_piece(t_player *player, t_filler *filler, char *line);
int			line_board(t_player *player, t_filler *filler, char *line);
void 		print_map(t_filler *filler);
int			update_map(t_filler *filler, t_player *player);
char		**init_map(t_filler *filler);
t_filler	*set_filler(t_filler *filler, char *line);
int			init_mid(t_filler *filler, int i, int j);
void		path_mid(t_filler *filler);
void		get_piece(char *line, t_player *player);
int			init_piece(char **line, t_player *player);
int			free_piece(t_player *player);
int			place_piece(t_filler *filler, t_player *player);
int			check_place(t_filler *filler, t_player *player, int y, int x);
void		set_piece_col(t_player *player);
void		set_piece_row(t_player *player);
void		print_piece(t_player *player);
void		start_bot(t_filler *filler);
void		start_top(t_filler *filler);
void		checker(t_filler *filler);