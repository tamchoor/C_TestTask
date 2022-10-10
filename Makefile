NAME = ff

CC = cc
FLAGS = -Wall -Werror -Wextra -g
# FLAGS = -Wall -Werror -Wextra -g -fsanitize=address
# LIBRARIES =  -lft -lreadline -L$(LIBFT_DIRECTORY)
# FLAGS = -Wall -Werror -Wextra -g

# FLAGS = -Wall -Werror -Wextra  -fsanitize=address -g
# LIBRARIES =  -lft -lreadline -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include -L$(LIBFT_DIRECTORY)
# INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS)

# HEADER = minishell.h wild_c/wild_card.h $(EXEC_D)executer.h
# HEADERS_DIRECTORY = .

# LIBFT = $(LIBFT_DIRECTORY)libft.a
# LIBFT_DIRECTORY = ./libft/
# LIBFT_HEADERS = $(LIBFT_DIRECTORY)

# SOURCES = minish.c env.c cd.c unset.c shlvl.c export.c find_meaning_in_env.c\
#

# BUILT_S = env.c cd.c unset.c shlvl.c export.c pwd.c exit.c echo.c export_utils.c print_env.c
# BUILT_D = built_ft/

# WILDC_S = wild_c.c find_parts.c find_meaning_star.c wild_c_utils.c
# WILDC_D = wild_c/

# EXEC_S = executer.c built_in_ft.c pipex.c status.c execut_utils.c
# EXEC_D = executer/

# PARSER_S = parser.c parser_utils.c parser_is_who.c\
# 			parser_exec_data_creat.c parser_exec_data_utils.c\
# 			parser_word_list_creat.c parser_word_list_utils.c\
# 			parser_syntax_check.c\
# 			parser_clear.c data_print.c

# PARSER_S = *.c

# PARSER_D = parser/

# DIR_SRC = $(OBJS_DIR)$(BUILT_D) $(OBJS_DIR)$(PARSER_D) $(OBJS_DIR)$(WILDC_D) $(OBJS_DIR)$(EXEC_D)

SOURCES_S =  main.c 
# $(addprefix built_ft/, $(BUILT_S)) \
# $(addprefix $(PARSER_D), $(PARSER_S)) \
# $(addprefix $(WILDC_D), $(WILDC_S)) \
# $(addprefix $(EXEC_D), $(EXEC_S)) \
# find_meaning_in_env.c find_var_dllr.c\
# heredoc.c ft_atol.c ft_error.c


OBJS = $(SOURCES_S:%.c=%.o)
OBJS_DIR = objs/
OBJECTS	= $(addprefix $(OBJS_DIR), $(OBJS))



GREEN = \033[0;32m
RED = \033[0;31m
CROSS = \033[9m
MARK = \033[7m
RESET = \033[0m

.PHONY: all clean fclean re bonus clno

all: $(NAME)

ALL_OBJS_DIR = $(DIR_SRC)

$(NAME): $(OBJECTS) $(LIBFT)
	@$(CC) $(FLAGS) $(INCLUDES)  $(LIBRARIES) $(OBJECTS) -o $(NAME)
	@echo "\n$(MARK) $(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(MARK) $(NAME): $(GREEN)$(NAME) was created$(RESET)"


$(OBJS_DIR)%.o : %.c $(HEADER)
	@mkdir -p $(OBJS_DIR)
# @mkdir -p  $(DIR_SRC)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

# $(LIBFT): $(LIBFT_DIRECTORY)/*.c $(LIBFT_DIRECTORY)/*.h
# 	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
# 	@$(MAKE) -sC $(LIBFT_DIRECTORY)

clean:
	@rm -rf $(OBJECTS) $(OBJS_DIR)
# @$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@echo "$(NAME): $(RED) $(CROSS)object $(RED) files were deleted$(RESET)"

fclean: clean
	@rm -rf $(NAME)
# @$(MAKE) -sC $(LIBFT_DIRECTORY) fclean
	@echo "$(CROSS) $(NAME) : $(RED)$(NAME) and $(BONUS_NAME) was deleted$(RESET)"

re: fclean all