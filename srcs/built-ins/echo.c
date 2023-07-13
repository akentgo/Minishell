#include "minishell.h"

//With this function we count the number of arguments so that we can check later on in the echo function
static int	nb_args(char **argv)
{
	unsigned int size;

	size = 0;
	while (argv[size])
		size++;
	return (size);
}

void echo(char **argv)
{
	unsigned int 	counter = 1;
	int				options = 0;

	if (nb_args(argv) > 1) //if there are more than 1 arguments, so not just echo
	{
		while (argv[counter] && ft_strcmp(argv[counter], "-n") == 0) //if the option -n has been read (echo -n) activate the aux variable
		{
			options = 1;
			counter++;
		}
		while (argv[counter]) //this is the base echo command
		{
			ft_putstr_fd(argv[counter], 1);
			if (argv[counter + 1] && argv[counter][0] != '\0')
				write(1, " ", 1);
			counter++;
		}
	}
	if (options == 0)
		write(1, "\n", 1);
	return (SUCCESS); //definimos success en la .h con valor 0
}
