#include <stdio.h>
#include <stdlib.h>
#include "./libft/includes/libft.h"

typedef struct	s_filler
{
	int width;
	int height;
	char **board;
	char **map;
}				t_filler;

typedef struct	s_piece
{
	int width;
	int height;
	int w_offset;
	int h_offset;
	char **piece;
}				t_piece;

typedef struct	s_player
{
	int player; /* p1, p2 */
	char player_char; /* X or O */
	char opp_char; /* X or O */
	t_piece *piece; /* Current piece */
}				t_player;

void print_player(int fd1, t_player *player);
void print_filler(int fd1, t_filler *filler);
void print_map(int fd1, t_filler *filler);
void print_piece(int fd1, t_piece *piece);
t_player *init_player(char *line);
t_filler *init_filler(char *line);
int update_board(t_filler *filler, t_player *player, char **line);
int update_map(t_filler *filler, t_player *player);
int init_mid(t_filler *filler);
// int place_piece(t_player *player, t_filler *filler, t_piece *piece);
t_piece *init_piece(int fd1, char **line);
// t_piece *reduce_piece(t_piece *piece);
int next_line();
