#include "../../include/minishell.h"

static	int	space_handler(char *str, int i)
{
	int	j;

	j = i;
	while (ft_isspace(str[i]) == 0 && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (i - 1);
	return (j);
}

static	int	double_quote_handler(char *cmd, char **env, int j)
{
	int		k;
	char	*val;

	k = 0;
	val = NULL;
	if (cmd[j] != '$' && cmd[j] != '"')
		write(1, &cmd[j], 1);
	else if (cmd[j] == '$')
	{
		j++;
		while (cmd[j + k] != '"'
			&& ft_isspace(cmd[j + k]) != 0 && cmd[j + k] != '\0')
			k++;
		val = ft_substr(cmd, j, k);
		print_env_var(env, val);
		j = j + k;
		j = space_handler(cmd, j);
		xfree(val);
		if (cmd[j] != '\0')
			write(1, " ", 1);
	}
	return (j);
}

static	int	quotes_handler(char *cmd, char **env, int j)
{
	if (cmd[j] == '\'' && cmd[j] != '\0')
	{
		while (cmd[++j] != '\'' && cmd[j] != '\0')
		{
			j = space_handler(cmd, j);
			write(1, &cmd[j], 1);
		}
		if (cmd[j] == '\'' && cmd[j] != '\0')
		{
			j++;
			write(1, " ", 1);
		}
	}
	else if (cmd[j] == '"' && cmd[j] != '\0')
	{
		while (cmd[++j] != '"' && cmd[j] != '\0')
		{
			j = double_quote_handler(cmd, env, j);
			if (cmd[j] == '"')
				break ;
		}
	}
	return (j);
}

static int	dollar_handler(char *cmd, char **env, int j)
{
	int		k;
	char	*var;

	k = 0;
	var = NULL;
	if (cmd[j] == '$' && cmd[j + 1] == '$')
		j++;
	else if ((cmd[j] == '$' && cmd[j + 1] == '"')
		|| (cmd[j] == '$' && cmd[j + 1] == '\''))
		j = quotes_handler(cmd, env, (j + 1));
	else if ((cmd[j] == '$' && (cmd[j + 1] == 0x20 || cmd[j + 1] == '\0')))
		write(1, "$", 1);
	else if (cmd[j] == '$')
	{
		j++;
		while (ft_isspace(cmd[j + k]) != 0 && cmd[j + k] != '\0')
			k++;
		var = ft_substr(cmd, j, k);
		print_env_var(env, var);
		j = j + k - 1;
	}
	return (j);
}

void	ft_echo(char *cmd, char **env)
{
	int		j;
//	int		k;
//	char	*val;
	j = -1;
	while (cmd[++j] != '\0')
	{
//		val = NULL;
//		k = 0;
		if (cmd[j] == '\'' || cmd[j] == '"')
			j = quotes_handler(cmd, env, j);
		else if (cmd[j] == '$')
			j = dollar_handler(cmd, env, j);
		else
		{
			j = space_handler(cmd, j);
			write(1, &cmd[j], 1);
		}
	}
}
