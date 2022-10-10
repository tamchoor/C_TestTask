#ifndef FIND_FILE_H
# define FIND_FILE_H

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



/* utils.c */

char		*ft_strjoin_path(char const *s1, char const *s2);
int			ft_strncmp_last(char *str1, char *str2, int len2);
void		print_all_parts(t_part	*parts_origin);
char		*ft_strdupl(char *str, size_t len);
int			write_error_and_exit(char *str1, char *str2, char *str3, int flag_perror);
char		*free_parts(t_part *first);
void		print_current_file_with_path(struct dirent *diren, char *dir);


/* parsing_filename.c */

t_part	*parsing_filename(char *filename);


/* check_filename.c */
int	check_filename_consists_parts(t_part *first, char *line);
/* find_filename.c */
void searching_in_current_dir(t_part	*parts);
void	find_filename(char *filename);



#endif