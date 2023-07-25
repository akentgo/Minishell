NAME = minishell

#HEADER = minishell.h

FLAGS = -Wall -Wextra -Werror

SRC_FILES = main.c prompt.c srcs/enviroment/envs.c srcs/enviroment/env_utils2.c srcs/enviroment/envs_utils.c srcs/enviroment/envs_search.c error.c expander.c args.c lexer.c \
			redir_splitter.c cmd_nodes.c get_files.c heredoc.c ft_trim.c builtins.c srcs/built-ins/cd.c srcs/built-ins/echo.c srcs/built-ins/pwd.c signals.c exec_cmd.c exec.c

LIBFT = libft/libft.a

OBJS = $(SRC_FILES:.c=.o)

CC = gcc

INCLUDE_DIRS = -L /Users/akent-go/.brew/opt/readline

all: $(NAME)

$(NAME): $(OBJS)
	@ make -C libft/
	@ $(CC) -I /usr/local/opt/readline/include -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include $(OBJS) -lreadline $(LIBFT) -o $(NAME)

%.o: %.c
	@ $(CC) -I ~/.brew/opt/readline/include -I /usr/local/opt/readline/include -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re