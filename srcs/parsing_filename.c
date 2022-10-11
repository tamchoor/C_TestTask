#include "find_file.h"


int	find_special_symb_in_line(char *line)
{
	int			i;
	static int	quote11;
	static int	quote22;

	i = 0;
	while (line && line[i])
	{
		if ((line[i] == '*' && i > 0 && quote11 % 2 == 0 && quote22 % 2 == 0)
			|| (line[i] == '?' && i > 0 && quote11 % 2 == 0 && quote22 % 2 == 0)
			|| (line[i] == '*' && i == 0) || (line[i] == '?' && i == 0) )
			return (i);
		if (line[i] == '\'' && quote22 % 2 == 0)
			quote11 += 1;
		if (line[i] == '"' && quote11 % 2 == 0)
			quote22 += 1;
		i++;
	}
	return (-1);
}

void	split_line(char *line, t_part *parts)
{
	int		len;
	int i = 0;

	while (line[i])
	{
		len = find_special_symb_in_line(line + i);
		if (len == -1)
		{
			parts->line = ft_strdupl((line + i), strlen((line + i)));
			if (!parts->line)
				write_error_and_exit("split_line:", 0, ": malloc error.\n", FP);
			return ;
		}
		else if (len == 0 && line[len + i] != '?')
		{
			parts->line = NULL;
			parts->flag = STAR;
		}
		else if (len == 0 && line[len + i] == '?')
		{
			parts->line = NULL;
			parts->flag = QUEST;
		}
		else if (len != 0)
			parts->line = ft_strdupl((line + i), len);
		if ((line[len + i] == '?' && len > 0) || (line[len + i] == '*' && len > 0))
			i = len + i;
		else
			i = len + i + 1;
		if (line[i])
		{
			parts->next = (t_part *) calloc (1, sizeof(t_part));
			if (!parts->next)
				write_error_and_exit("split_line:", 0, ": malloc error.\n", FP);
			parts = parts->next;
		}
	}
}

int	delete_quotes_from_parts(t_part *parts)
{
	t_part		*f_parts = parts;
	int quotes = 0;
	int quotes2 = 0;
	int i = 0;
	int j = 0;

	while (f_parts)
	{
		i = 0;
		j = 0;
		while (f_parts->line && f_parts->line[i])
		{
			if (f_parts->line[i] == '\'' && quotes2 % 2 == 0)
				quotes++;
			else if (f_parts->line[i] == '"' && quotes % 2 == 0)
				quotes2++;
			else
				f_parts->line[j++] = f_parts->line[i];
			i++;
			if (f_parts->line[i] == '\0')
				f_parts->line[j] = '\0';
		}
		if (f_parts && f_parts->next && f_parts->next->flag == QUEST && f_parts->flag == STAR)
			f_parts->next->flag = STAR;
		f_parts = f_parts->next;
	}
	return (0);
}

/* Парсинг названия файла по сепараторам ? и * в односвязный список*/
t_part	*parsing_filename(char *filename)
{
	t_part	*parts;
	t_part	*first;

	parts = (t_part *) calloc (1, sizeof(t_part));
	if (!parts)
		write_error_and_exit("find_parts:", 0, ": malloc error.\n", FLAG_PERROR);
	first = parts;
	split_line(filename, parts);
	delete_quotes_from_parts(parts);
	// print_all_parts(parts);
	return (first);
}
