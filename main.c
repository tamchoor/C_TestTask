#include "find_file.h"

int main(int argc, char **argv)
{
	if (argc == 2 || argc == 3)
	{
		if (argc == 3)
		{
			if (chdir(argv[2]) == -1)
			{
				write_error_and_exit("main:", argv[2], ": chdir error.\n", FP);
				return 1;
			}
		}
		if (argv[1][0] != '\0')
			find_filename(argv[1]);
		return 0;
	}
	write(2, "For call program use ./ff filename [dirname]\n", 45);
	return 1;
}
