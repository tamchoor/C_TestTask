#include "find_file.h"

void	cycle_through_files(DIR *direct, struct dirent *diren, t_part *first, char *dir)
{
	char *new_dir;

	while (diren != NULL)
	{
		if (diren->d_type == 4 && diren->d_name[0] != '.')
		{
			new_dir = ft_strjoin_path(dir, diren->d_name);
			if (chdir(new_dir) != -1)
			{
				searching_in_current_dir(first);
			}
			else
			{
				write(2, "Cant check dir - ", 17);
				write(2, diren->d_name, strlen(diren->d_name));
			}
			free(new_dir);
		}
		if (check_filename_consists_parts(first, diren->d_name) == 0)
		{
			print_current_file_with_path(diren, dir);
		}
		diren = readdir(direct);
	}
}

void searching_in_current_dir(t_part	*parts)
{

	char			*dir;
	DIR				*direct;
	struct dirent	*diren;

	dir = NULL;
	dir = getcwd(dir, PATH_MAX);
	if (dir == NULL)
		write_error_and_exit("searching_in_current_dir:", 0, ": getcwd error.\n", FP);
	direct = opendir(dir);
	diren = readdir(direct);
	cycle_through_files(direct, diren, parts, dir);
	free(dir);
	if (closedir(direct) == -1)
		write_error_and_exit("searching_in_current_dir:", 0, ": closedir error.\n", FP);
}

void	find_filename(char *filename)
{
	t_part	*parts;

	parts = parsing_filename(filename);
	searching_in_current_dir(parts);
	free_parts(parts);
}
