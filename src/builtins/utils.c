#include "minishell.h"

void	free_tab(char **old_tab)
{
	int i;

	if (!old_tab)
		return ;
	i = -1;
	while (old_tab[++i])
		free(old_tab[i]);
	free(old_tab);
}