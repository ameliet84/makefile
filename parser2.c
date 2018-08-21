#include "bsq2.h"

char	*file_read(char *argv, int *line, int *col, char elts[3])
{
	char *str;
	char buff[4];
	int fd;

	*line = 0;
	*col = 0;
	fd = open(argv, O_RDONLY);
	while (read(fd, buff, 1) && (buff[0] >= '0' && buff[0] <= '9'))
		*line = *line * 10 + buff[0] - '0';
	elts[0] = buff[0];
	read(fd, buff, 3);
	elts[1] = buff[0];
	elts[2] = buff[1];
	elts[3] = '\0';
	while (read(fd, buff, 1) && buff[0] != '\n')
		(*col)++;
	close(fd);
	fd = open(argv, O_RDONLY);
	if (!(str = (char *)malloc(sizeof(char ) * (*line * *col +	*line))))
		return (NULL);
	while (read(fd, buff, 1) && (buff[0] >= '0' && buff[0] <= '9'))
		*line = *line;
	read(fd, buff, 3);
	read(fd, str, (*line * *col + *line));
	str[*line * *col + *line] = '\0';
	close(fd);
	return (str);
}

int	solve_bsq(t_elt **tab, t_sol *sol, int pos, t_coord size)
{
	int c;

	if (pos >= size.line * size.col)
		return (1);
//	printf("%d et %d\n", pos, size.line * size.col );
//	fflush(stdout);
	if(pos < size.line * size.col && (tab[pos / size.col][pos % size.col].col <= sol->max))
	{
		return solve_bsq(tab, sol, pos + size.col - pos % size.col, size);
	}
	if(pos < size.line * size.col && (tab[pos / size.col][pos % size.col].line <= sol->max))
	{
		return solve_bsq(tab, sol, pos + 1, size);
	}
	if (pos < size.line * size.col && sol->max < (c = test_pos(pos, size, tab)))
		{
			sol->max = c;
			(sol->pos).line = pos / size.col;
			(sol->pos).col = pos % size.col;
		}
	return solve_bsq(tab, sol, pos + 1, size);
}

/*
t_coord	solve_bsq(t_elt **tab, int *max, t_coord size)
{
	int c;
	t_coord sol;
	t_coord pos;

	pos.line = -1;
	while(++pos.line < size.line * size.col)
	{
		pos.col = *max;
		if((size.line - pos.line / size.col <= *max))
	//		(size.col - pos.line % size.col <= *max))
			return (sol);
		while (pos.line < size.line * size.col && 
			(tab[pos.line / size.col][pos.line % size.col].col <= pos.col))
			pos.line = pos.line + size.col - pos.line % size.col;
		while (pos.line < size.line * size.col && 
			(tab[pos.line / size.col][pos.line % size.col].line <= pos.col))
			++pos.line;
		if (pos.line < size.line * size.col &&
			*max < (c = test_pos(pos, size, tab)))
		{
			*max = c;
//			printf("pos = %d et max %d\n", pos.line, *max);
			sol.line = pos.line / size.col;
			sol.col = pos.line % size.col;
		}
	}
	printf("%d et %d\n", sol.line, sol.col);
	return (sol);
}
*/
void	fill_tab(t_elt **tab, t_coord size, char *str, char elts[3])
{
	int i;
	int j;

	i = -1;
	tab[0][0].empty = elts[0];
	tab[0][0].obst = elts[1];
	tab[0][0].full = elts[2];
	while(++i < size.line)
	{
		j = -1;
		while (++j < size.col)
		{
			tab[i][j].car = str[i * size.col + j + i];
			if(tab[i][j].car == elts[1])
			{
				tab[i][j].line = 0;
				tab[i][j].col = 0;
			}
			else if (i == 0 || tab[i - 1][j].car == elts[1])
			{
				tab[i][j].line = get_line(str, elts, i * size.col + j + i,
					size.col);
					if (j == 0 || tab[i][j - 1].car == elts[1])
							tab[i][j].col = get_col(str, elts, i * size.col + j + i, size);
					else
						tab[i][j].col = tab[i][j - 1].col - 1;
			}
			else
			{
				tab[i][j].line = tab[i - 1][j].line - 1;
				if (j == 0 || tab[i][j - 1].car == elts[1])
						tab[i][j].col = get_col(str, elts, i * size.col + j + i, size);
				else
					tab[i][j].col = tab[i][j - 1].col - 1;
			}

		}
	}
}

t_elt	**parser(char *str, int columns, int lines, char elts[3])
{
	int i;
	t_elt **tab;
	t_coord size;

	size.line = lines;
	size.col = columns;
	//printf("la\n");
	if(!(tab = (t_elt**)malloc(sizeof(t_elt *) * lines)))
		return (NULL);
	i = -1;
	while(++i < lines)
		if(!(tab[i] = (t_elt*)malloc(sizeof(t_elt) * columns)))
			return (NULL);
	fill_tab(tab, size, str, elts);
//	printf("fin\n");
	return (tab);
}

void	bsq(char *str)
{
	t_coord size;
	char *str2;
	char elts[3];
	t_elt **tab;
	t_sol sol;

	sol.max= 0;
	str2 = file_read(str, &size.line, &size.col, elts);
	tab = parser(str2, size.col, size.line, elts);
	solve_bsq(tab, &sol, 0, size);
	sol_tab(tab, sol);
	fill_str(str2, tab, size);
	print_str(str2, size);
//	print_tab(tab, size.line, size.col);
	printf("line = %d et col = %d max = %d\n", sol.pos.line, sol.pos.col, sol.max);
	free(str2);
	free(tab);
}

void		error(int n, char *str)
{
	ft_putstr("bsq: ");
	ft_putstr(str);
	if (n == 2)
		ft_putstr(": No such file or directory\n");
	else
		ft_putstr(": Permission denied\n");
}

int			main(int argc, char **argv)
{
	int i;
	int fd;

	if (argc == 1)
		write(1, "Yoann, gere ca!!!\n", 18);
	else
	{
		i = 0;
		while (++i < argc)
		{
			errno = 0;
			if ((fd = open(argv[i], O_RDONLY)) == -1)
				error(errno, argv[i]);
			else
				bsq(argv[i]);
			close(fd);
			if (i != argc - 1)
				write(1, "\n", 1);
		}
	}
	return (0);
}
