#include "bsq2.h"

void		ft_putstr(char *str)
{
	while (*str)
		write(2, str++, 1);
}

int		ft_atoi(char *str)
{
	unsigned int	nbr;
	int				sign;

	sign = 1;
	nbr = 0;
	while ((*str > 8 && *str < 14) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
		sign = (*str++ == '-') ? -1 : 1;
	while (*str >= '0' && *str <= '9')
		nbr = nbr * 10 + *str++ - '0';
	return (sign * nbr);
}

int	get_line(char *str, char elts[3], int pos, int columns)
{
	int i;

	i = pos;
	while(++i % (columns + 1) != 0 && str[i] != '\n')
		if(str[i] == elts[1])
			return (i - pos);
	return (i - pos);
}

void	fill_str(char *str, t_elt **tab, t_coord size)
{
	int i;
	int j;
	int k;

	i = -1;
	k = -1;
	while(++ i < size.line)
	{
		j =-1;
		while (++j < size.col)
			str[++k] = tab[i][j].car;
		str[++k] = '\n';
	}
	str[++k] = '\0';
}

int	get_col(char *str, char elts[3], int pos, t_coord size)
{
	int i;
	int j;

	i = pos;
	j = pos;
	while(i < size.line * size.col + size.line)
	{
		if(str[i] == elts[1])
			return (j - pos);
		i += size.col + 1;
		++j;
	}
	return (j - pos);
}

int test_square(int pos, int max, t_coord size, t_elt **tab)
{
	int i;
	int j;
	int k;

	k = -1;
	i = pos / size.col;
	j = pos % size.col;
	if( i + max >= size.line || j + max >= size.col)
		return (0);
	while (++k <= max && j + k < size.col)
		if (tab[i + max][j + k].car == tab[0][0].obst)
			return (0);
	k = -1;
	while (++k <= max && i + k < size.line)
	{
		if (tab[i + k][j + max].car == tab[0][0].obst)
			return (0);
	}
	return (1);
}

int	test_pos(int pos, t_coord size, t_elt **tab)
{
	int max;

	max = 0;
	while(test_square(pos, max, size, tab) == 1)
		++max;
	return (max);
}

void	sol_tab(t_elt **tab, t_sol sol)
{
	int i;
	int j;

	i = -1;
	while(++i < sol.max)
	{
		j = -1;
		while(++j < sol.max)
			tab[(sol.pos).line + i][(sol.pos).col + j].car = tab[0][0].full;
	}
}
void	print_str(char *str, t_coord size)
{
	write(1, str, size.line * size.col + size.line);
}
void	print_tab(t_elt **tab, int line, int column)
{
	int i;
	int j;

	i = -1;
	while(++i < line)
	{
		j = -1;
		while (++j < column)
			write(1, &tab[i][j].car, 1);
		write(1, "\n", 1);
	}
}