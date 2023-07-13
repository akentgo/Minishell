#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
int main(int argc, char **argv)
{
	const char *line = NULL;
	const char *bye = "bye";
	while (1)
	{
	
	line = readline("Test-Prompt: ");
	printf("%s\n", line);
	if (!ft_strncmp(line, bye, 3))
		exit(0);
	}
	return (0);
}
