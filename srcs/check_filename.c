#include "find_file.h"

int	checking_one_part(t_part *first, char *line, int *i, int flag)
{
	int	res_cmp;

	if (flag == FIRST)
	{
		if (first && first->line != NULL)
		{
			if (memcmp(line, first->line, strlen(first->line)) != 0)
				return (-1);
			*i = strlen(first->line);
		}
		if (first && !first->line)
		{
			*i = *i + 1;
		}
	}
	if (flag == LAST)
	{
		if (first && first->line != NULL && first->flag == QUEST) // ./ff "?'?'.*"  "*.*" 
		{
			// *i = *i + 1;
			if (memcmp((line + *i), first->line, strlen(first->line)) != 0)
				return (-1);
			*i = *i + strlen(first->line);
			if (!line[*i])
				return (0);
			return (-1);
		}
		else if (first && first->line != NULL)
		{
			res_cmp = ft_strncmp_last((line + *i), first->line, 
					strlen(first->line));
			if (res_cmp != 0)
				return (-1);
		}
		else if (first && !first->line && first->flag == QUEST)
		{
			if (line[*i] && !line[*i + 1])
				return (0);
			return (-1);
		}
	}
	return (0);
}

int	checking_mid_parts(t_part *parts, t_part *last_p, char *line, int *i, int prev_flag)
{
	int	res_cmp = -1;
	int	prev_part = prev_flag;

	while (parts && parts != last_p)
	{
		if (parts->line)
		{
			if (prev_part == STAR)
			{
				res_cmp = -1;
				while (line[*i])
				{
					res_cmp = memcmp((line + *i), parts->line,
							strlen(parts->line));
					*i = *i + 1;
					if (res_cmp == 0)
						break ;
				}
				*i = *i + strlen(parts->line) - 1;
			}
			else if (prev_part == QUEST)
			{
				// *i = *i + 1;
				res_cmp = -1;
				if (line[*i])
					res_cmp = memcmp((line + *i), parts->line,
							strlen(parts->line));
				*i = *i + strlen(parts->line);
			}
			if (res_cmp != 0)
				return (-1);
			// prev_part = 0;
		}
		if(!parts->line)
		{
			if (parts->flag == STAR)
				prev_part =  STAR;
			if (parts->flag == QUEST)
			{
				*i = *i + 1;
				prev_part = QUEST;
			}
		}
		parts = parts->next;
	}
	if (parts && parts == last_p)
	{
		// if (!last_p->line && last_p->flag == QUEST)
		// 	*i = *i - 1;
		if (last_p->line)
			last_p->flag = prev_part;
	}
	return (0);
}

int	check_filename_consists_parts(t_part *first, char *line)
{
	t_part	*parts;
	t_part	*last_p;
	int		i;

	if (first->next)
	{
		parts = first->next;
		last_p = first->next;
		while (last_p->next)
			last_p = last_p->next;
		i = 0;
		if ((first->line && first->line[0] != '.') || first->line == NULL)
		{
			if (memcmp(line, ".", 1) == 0)
				return (-1);
		}
		if (checking_one_part(first, line, &i, FIRST) == -1)
			return (-1);
		if (checking_mid_parts(parts, last_p, line, &i, first->flag) == -1)
			return (-1);
		if (checking_one_part(last_p, line, &i, LAST) == -1)
			return (-1);
	}
	else
	{
		i = 0;
		if ((first->line && first->line[0] != '.') || first->line == NULL)
		{
			if (memcmp(line, ".", 1) == 0)
				return (-1);
		}
		if (checking_one_part(first, line, &i, FIRST) == -1)
			return (-1);
		if (line[i])
			return (-1);
	}
	return (0);
}
