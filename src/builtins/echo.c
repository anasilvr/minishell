#include "../../include/minishell.h"

void	ft_echo(char **cmd, int i)
{
	int		j;
	
	j = -1;
	while (cmd[i] != NULL)
	{
		while (cmd[i][++j] != '\0')
        	write(1, &cmd[i][j], 1);
		j = -1;
		i++;
		write(1, " ", 1);
	}
}
