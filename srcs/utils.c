#include "find_file.h"

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

void	print_current_file_with_path(struct dirent *diren, char *dir)
{
	write (1, dir, strlen(dir));
	write (1, "/", 1);
	write(1, diren->d_name, strlen(diren->d_name));
	write (1, "\n", 1);
}
