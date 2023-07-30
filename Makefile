NAME = minishell

FLAGS = -Wall -Wextra -Werror

SRC_FILES = srcs/main.c srcs/enviroment/envs.c srcs/enviroment/env_utils2.c srcs/enviroment/envs_utils.c srcs/enviroment/envs_search.c srcs/error.c srcs/expander.c srcs/args.c srcs/lexer.c \
			srcs/redir_splitter.c srcs/cmd_nodes.c srcs/get_files.c srcs/heredoc.c srcs/ft_trim.c srcs/builtins.c srcs/built-ins/cd.c srcs/built-ins/echo.c srcs/built-ins/pwd.c srcs/signals.c srcs/exec_cmd.c srcs/exec.c \
			srcs/utils.c srcs/cmd_nodes_utils.c srcs/error_utils.c

LIBFT = ./libft/libft.a

OBJS_DIRS = objs
OBJS = $(addprefix $(OBJS_DIRS)/, $(SRC_FILES:.c=.o))

CC = gcc

INCLUDE_DIRS = -L /Users/akent-go/.brew/opt/readline

all: $(OBJS_DIRS) $(NAME)

$(shell mkdir -p $(dir $(OBJS)))

$(NAME): $(OBJS)
	@ echo "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗"
	@ echo "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║"
	@ echo "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║"
	@ echo "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
	@ echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
	@ echo 
	@ echo 						Making Libft...🥱
	@ make -C libft/
	@ echo 					"Compiling Minishell...🤓"
	@ $(CC) -I /usr/local/opt/readline/include -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include $^ -lreadline $(LIBFT) -o $(NAME)

$(OBJS_DIRS)/%.o: %.c | $(OBJS_DIRS)
	@ $(CC) -I ~/.brew/opt/readline/include -I /usr/local/opt/readline/include -c $< -o $@

$(OBJS_DIRS):
	@ mkdir -p $(OBJS_DIRS)
	@ mkdir -p $(dir $(OBJS))

clean:
	@ rm -rf $(OBJS)
	@ rm -rf $(OBJS_DIRS)
	@ make -C libft/ clean

fclean: clean
	@ rm -f $(NAME)
	@ make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re