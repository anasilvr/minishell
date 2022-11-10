#include "minishell.h"

int	ft_cmp_builtin(const char *str1, const char *str2, size_t n)
{
	unsigned int	i;

	i = -1;
	if (n == 0)
		return (-1);
	while (++i < (n - 1) && str1[i] == str2[i] && 
        (str1[i] != '\0' && str2[i] != '\0'))
		;
    if (str2[i + 1] == '\0' && str1[i + 1] == '\0')
        return (0);
	return (-1);
}

void	exit_handler(char **instruct)
{
    if (ft_cmp_builtin(instruct[0], "exit", 4) == 0)
		exit(EXIT_SUCCESS);
}

char **builtins_checker(char **instruct, char **env)
{
	echo_handler(instruct, env);
	pwd_handler(instruct, env);
	env_handler(instruct, env);
	env = cd_handler(instruct, env);
	env = export_handler(instruct, env);
	env = unset_handler(instruct, env);
	exit_handler(instruct);
	return (env);
}
