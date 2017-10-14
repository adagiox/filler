#include <stdio.h>
#include <stdlib.h>
#include "./libft/includes/libft.h"

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
	int player;
	char player_char;
	char opp_char;
	int p_cols;
	int p_rows;
	int col_offset;
	int row_offset;
	char **piece;
}				t_player;

// void print_player(int fd1, t_player *player);
// void print_filler(int fd1, t_filler *filler);
void print_map(t_filler *filler);
t_player *init_player(char *line);
t_filler *init_filler(char *line);
int update_board(t_filler *filler, t_player *player, char **line);
int update_map(t_filler *filler, t_player *player);
int init_mid(t_filler *filler);

int next_line();

void	get_piece(char *line, t_player *player);
void	init_piece(char **line, t_player *player);
void	set_offset(t_player *player);
void	set_piece_col(t_player *player);
void	set_piece_row(t_player *player);
void	set_offset(t_player *player);
int		check_place(t_filler *filler, t_player *player, int y, int x);
void	print_piece(t_player *player);
void	checker(t_filler *filler);