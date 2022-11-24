#include "minishell.h"

void	free_tab(char **old_tab)
{
	int i;

	if (!old_tab)
		return ;
	i = -1;
	while (old_tab[++i])
		xfree(old_tab[i]);
	xfree(old_tab);
}

int ft_free_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
		;
	free(str);
	return(i);
}