void	free_tab(char **tab)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (tab[i])
	{
		if (tab[i])
		{
			free (tab[i]);
			tab[i] = NULL;
		}
		i++;
	}
	if (tab)
		free (tab);
}
