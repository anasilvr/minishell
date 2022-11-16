#include "minishell.h"

void	env_handler(char **instruct, t_data *data)
{
	if (ft_cmp_builtin(instruct[0], "env", 3) == 0)
		print_env(data->envp_cp);
}

void print_env(char **env)
{
    int     i;
    int     j;

    i = 0;
    j = -1;
	while (env[i] != NULL && ft_cmp_env(env[i], "PATH", 4) != 0)
		i++;
	if (env[i] != NULL)
		i = 0;
    while (env[i] != NULL)
    {
        while (env[i][++j] != '\0')
            write(1, &env[i][j], 1);
        j = -1;
		i++;
        write(1, "\n", 1);
    }
}

char **cpy_env(char **envp, int line)
{
	int i;
	int j;
	char **r_env;

	i = -1;
	while (envp[++i] != NULL)
		;
	r_env = malloc(sizeof(char *) * (i + 1 + line));
	i = -1;
	while (envp[++i] != NULL)
	{
		j = -1;
		r_env[i] = malloc(sizeof(char *) * ft_strlen(envp[i]) + 1);
		while (envp[i][++j] != '\0')
			r_env[i][j] = envp[i][j];
	}
	r_env[i] = NULL;
	return (r_env);
}

int ft_cmp_env(char *str1, char *str2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0 || str1[0] == '\0' || !str2)
		return (-1);
	while (str1[i] == str2[i] && i < (n - 1) && 
        (str1[i] != '=' && str2[i] != '\0'))
		i++;
    if (str2[i + 1] == '\0' && str1[i + 1] == '=')
        return (0);
	return (-1);
}
