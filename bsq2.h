#ifndef _BSQ2_H_
#define _BSQ2_H_


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h> 
#include <string.h>

typedef struct s_coord
{
	int line;
	int col;
}				t_coord;

typedef struct  s_elt
{
	char car;
	int line;
	int col;
	char empty;
	char obst;
	char full;
} t_elt;

typedef struct s_sol
{
	int max;
	t_coord	pos;
} t_sol;

void		ft_putstr(char *str);
int		ft_atoi(char *str);
int	get_line(char *str, char elts[3], int pos, int columns);
int	get_col(char *str, char elts[3], int pos, t_coord size);
void	print_tab(t_elt **tab, int line, int column);
int	test_pos(int pos, t_coord size, t_elt **tab);
void	sol_tab(t_elt **tab, t_sol sol);
void	fill_str(char *str, t_elt **tab, t_coord size);
void	print_str(char *str, t_coord size);
int	solve_bsq(t_elt **tab, t_sol *sol, int pos, t_coord size);


#endif