#include <stdio.h>
#include <stdlib.h>
#include "./libft/includes/libft.h"

typedef struct	s_player
{
	unsigned int player:1; /* 0 - p1, 1 - p2 */
	char player_char; /* X or O */

}				t_player;

void print_player(int fd1, t_player *player);
t_player *init_player(char *line);
int next_line();
