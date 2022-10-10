
#include <libc.h>
#include <dirent.h>

# define FLAG_PERROR	19
# define FP				19

# define STAR			42
# define QUEST			63

# define FIRST			1
# define LAST			2



typedef struct s_part
{
	char			*line;
	int 			flag;
	struct s_part	*next;
}	t_part;

int searching_in_current_dir(t_part	*parts);

char	*ft_strjoin_path(char const *s1, char const *s2)
{
	char	*dest;
	size_t	lens1;
	size_t	lens2;
	size_t	i;

	if (s1 == 0 || s2 == 0)
		return (0);
	lens1 = strlen(s1);
	lens2 = strlen(s2);
	dest = (char *) calloc((lens1 + lens2 + 1 + 1), sizeof(char));
	if (!dest)
		return (0);
	memcpy(dest, s1, lens1);
	dest[lens1++] = '/';
	i = 0;
	while (lens2 > 0)
	{
		dest[lens1] = s2[i];
		lens2--;
		lens1++;
		i++;
	}
	dest[lens1] = '\0';
	return (dest);
}

int	ft_strncmp_last(char *str1, char *str2, int len2)
{
	int	len1;

	len1 = strlen(str1) - 1;
	len2 = len2 - 1;
	if (len1 >= len2)
	{
		while (len2 >= 0)
		{
			if (str1[len1] != str2[len2])
				return (str1[len1] - str2[len2]);
			len1--;
			len2--;
		}
		return (0);
	}
	else
	{
		return (-1);
	}
	return (0);
}

void		print_all_parts(t_part	*parts_origin)
{
	t_part	*parts = parts_origin;

	write(1, "parts:\n", 7);
	while (parts)
	{
		if (parts->line)
			write(1, parts->line, strlen(parts->line));
		else
		{
			write(1, "NULL ", 5);
			write(1, &parts->flag, 1);
		}
		write(1, "\n", 1);
		parts = parts->next;
	}
	write(1, "end\n", 4);
}

char	*ft_strdupl(char *str, size_t len)
{
	char	*newstr;
	size_t	i;

	if (strlen(str) < len)
		len = strlen(str);
	newstr = calloc(len + 1, sizeof(char));
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		newstr[i] = str[i];
		i++;
	}
	return (newstr);
}

int	write_error_and_exit(char *str1, char *str2, char *str3, int flag_perror)
{
	write(2, "ff: ", 4);
	if (str1)
		write(2, str1, strlen(str1));
	if (flag_perror == FLAG_PERROR)
		perror(str2);
	else
	{
		if (str2)
			write(2, str2, strlen(str2));
		if (str3)
			write(2, str3, strlen(str3));
		else
			write(2, "Error.\n", 7);
	}
	exit (1);
}


char	*free_parts(t_part *first)
{
	t_part	*parts;
	t_part	*tmp;

	parts = first ;
	while (parts)
	{
		tmp = parts;
		parts = parts->next;
		free(tmp->line);
		free(tmp);
	}
	return (0);
}

int	is_star_in_line(char *line)
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
	// t_part	*parts_or = parts;

	while (line[i])
	{
		len = is_star_in_line(line + i);
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
		// print_all_parts(parts_or);
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
		f_parts = f_parts->next;
	}
	return (0);
}

t_part	*find_parts(char *line)
{
	t_part	*parts;
	t_part	*first;
	// int		i;

	parts = (t_part *) calloc (1, sizeof(t_part));
	if (!parts)
		write_error_and_exit("find_parts:", 0, ": malloc error.\n", FLAG_PERROR);
	first = parts;
	split_line(line, parts);
	return (first);
}

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
		if (first && first->line != NULL && first->flag == QUEST)
		{
			if (memcmp((line + *i), first->line, strlen(first->line)) != 0)
				return (-1);
		}
		else if (first && first->line != NULL)
		{
			res_cmp = ft_strncmp_last((line + *i), first->line,
					strlen(first->line));
			if (res_cmp != 0)
				return (-1);
		}
	}
	return (0);
}

int	checking_mid_parts(t_part *parts, t_part *last_p, char *line, int *i, int prev_flag)
{
	int	res_cmp;
	int	prev_part = prev_flag;

	while (parts && parts != last_p)
	{
		if (parts->line)
		{
			if (prev_part == 0)
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
			}
			else if (prev_part == 1)
			{
				res_cmp = -1;
				if (line[*i])
					res_cmp = memcmp((line + *i), parts->line,
							strlen(parts->line));
			}
			if (res_cmp != 0)
				return (-1);
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
		last_p->flag = prev_part;
	}
	return (0);
}


int	check_filename_and_parts(t_part *first, char *line)
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
		// write(1, "a\n", 2);
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
	}
	return (0);

}


void	cycle_through_files(DIR *direct, struct dirent *diren, t_part *first, char *dir)
{
	char *new_dir;

	// f_mean = *mean;
	while (diren != NULL)
	{
		// write(1, "aa\n", 3);

		if (diren->d_type == 4 && diren->d_name[0] != '.')
		{
			// printf("%d - diren->d_type  | %s - name \n", diren->d_type,  diren->d_name);
			new_dir = ft_strjoin_path(dir, diren->d_name);
			// new_dir = diren->d_name;
			if (chdir(new_dir) != -1)
			{
				// write(1,"SEARCH IN NEW DIR\n", 18);
				searching_in_current_dir(first);
			}
			else
			{
				write(2, "Cant check dir - ", 17);
				write(2, diren->d_name, strlen(diren->d_name));
			}
			free(new_dir);
		}
		if (check_filename_and_parts(first, diren->d_name) == 0)
		{
			write (1, dir, strlen(dir));
			write (1, "/", 1);
			write(1, diren->d_name, strlen(diren->d_name));
			write (1, "\n", 1);
		}
		diren = readdir(direct);
	}
}

int searching_in_current_dir(t_part	*parts)
{
	// t_part	*parts;

	char			*dir;
	DIR				*direct;
	struct dirent	*diren;
	// t_part			*mean;
	// t_part			*f_mean;

	dir = NULL;
	dir = getcwd(dir, PATH_MAX);
	if (dir == NULL)
		write_error_and_exit("searching_in_current_dir:", 0, ": getcwd error.\n", FP);
	direct = opendir(dir);
	// mean = (t_part *) calloc(sizeof(t_part), 1);
	// f_mean = mean;
	// if (!mean || !direct)
	// 	ft_errors_and_exit("wild_cards:", 0, ": malloc error.\n", FLAG_PERROR);
	diren = readdir(direct);
	cycle_through_files(direct, diren, parts, dir);
	// if (f_mean->line == NULL && f_mean->next == NULL)
	// 	ft_free_mean(&f_mean);
	if (closedir(direct) == -1)
		write_error_and_exit("searching_in_current_dir:", 0, ": closedir error.\n", FP);
	// return (f_mean);
	free(dir);
	// free_parts(parts);
	return 0;
}

int parsing_filename(char *filename)
{
	t_part	*parts;

	parts = find_parts(filename);
	// print_all_parts(parts);
	delete_quotes_from_parts(parts);
	// print_all_parts(parts);

	searching_in_current_dir(parts);

	free_parts(parts);
	return 0;
}

int main(int argc, char **argv)
{
	// printf("agc = %d\n", argc);
	if (argc == 2 || argc == 3)
	{
		if (argc == 3)
		{
			if (chdir(argv[2]) == -1)
			{
				write_error_and_exit("main:", 0, ": chdir error.\n", FP);
				return 1;
			}
		}
		parsing_filename(argv[1]);
		return 0;
	}
	write(2, "For call program use ff filename [dirname]\n", 43);
	return 1;
}