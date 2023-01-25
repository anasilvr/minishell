#include "../../include/minishell.h"

void	ft_echo(char *cmd, char **env)
{
	int		j;
	j = -1;
	while (cmd[++j] != '\0')
	{
        j = space_handler(cmd, j);
        write(1, &cmd[j], 1);
	}
}
