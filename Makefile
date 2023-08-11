COLOR_RESET = \033[0m
COLOR_BOLD = \033[1m
COLOR_RED = \033[91m
COLOR_BLUE = \033[94m
COLOR_GREEN = \033[92m
COLOR_YELLOW = \033[93m

NAME = minishell

FLAGS = -Wall -Wextra -Werror

SRC = $(BIN) $(BUILTINS) $(ENVIRONMENT) srcs/signals/signals.c

BIN = $(addprefix srcs/bin/, $(BIN_FILES))
BIN_FILES = args.c builtins.c cmd_nodes_utils.c cmd_nodes.c error_utils.c error.c exec_cmd.c exec.c expander.c ft_trim.c ft_trimcmd.c get_files.c heredoc.c \
			lexer.c main.c redir_splitter.c utils.c

BUILTINS = $(addprefix srcs/builtins/, $(BUILTIN_FILES))
BUILTIN_FILES = cd.c echo.c pwd.c

ENVIRONMENT = $(addprefix srcs/environment/, $(ENVIRONMENT_FILES))
ENVIRONMENT_FILES = env_utils2.c env_utils3.c envs_search.c envs_utils.c envs.c

FILES = $(SRC:srcs/%=%)

LIBFT = ./libft/libft.a

OBJS_DIRS = objs
OBJS = $(addprefix $(OBJS_DIRS)/, $(SRC:srcs/%.c=%.o)) # Update the object file paths, also, @D creates the neccesary subdirectories for each file, since we have different files in and out of folders

CC = gcc

INCLUDE_DIRS = -L /Users/akent-go/.brew/opt/readline

all: $(OBJS_DIRS) $(NAME)

$(OBJS_DIRS)/%.o: srcs/%.c
	@ mkdir -p $(@D) 
	@ $(CC) -I ~/.brew/opt/readline/include -I /usr/local/opt/readline/include -c $< -o $@

$(NAME): $(OBJS)
	@ echo 
	@ echo "$(COLOR_BLUE)███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗$(COLOR_RESET)"
	@ echo "$(COLOR_BLUE)████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║$(COLOR_RESET)"
	@ echo "$(COLOR_BLUE)██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║$(COLOR_RESET)"
	@ echo "$(COLOR_BLUE)██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║$(COLOR_RESET)"
	@ echo "$(COLOR_BLUE)██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗$(COLOR_RESET)"
	@ echo "$(COLOR_BLUE)╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝$(COLOR_RESET)"
	@ echo 
	@ echo 						Making Libft...🥱
	@ make -C libft/
	@ echo 					"Compiling Minishell...🤓"
	@ $(CC) -I /usr/local/opt/readline/include -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include $^ -lreadline $(LIBFT) -o $(NAME)

$(OBJS_DIRS):
	@ mkdir -p $(OBJS_DIRS)

clean:
	@ echo "\n🧹Limpiando archivos de $(NAME)...🧹\n"
	@ rm -rf $(OBJS)
	@ rm -rf $(OBJS_DIRS)
	@ make -C libft/ clean > /dev/null 2>&1

fclean: clean
	@ rm -f $(NAME)
	@ make -C libft/ fclean > /dev/null 2>&1

re: fclean all

.PHONY: all clean fclean re