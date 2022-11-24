#include "minishell.h"

int check_env_var(char **env, char *var)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (env[i] != NULL)
    {
        while (env[i][j] == var[j] && var[j] != '\0')
            j++;
        if (var[j] == '\0' && env[i][j] == '=')
            break ;
        j = 0;
        i++;
    }
    if (env[i] == NULL)
        return (-1);
    return (i);
}

t_data *unset_handler(char **instruct, t_data *data)
{
    int     i;
    int     r_check;
    char    **r_env;

    i = 0;
    r_env = data->envp_cp;
	if (ft_cmp_builtin(instruct[i] , "unset", 5) == 0 && instruct[i + 1] != NULL)
    {
        while (instruct[++i] != NULL)
        {
            r_check = check_env_var(r_env, instruct[i]);
            r_env = cpy_unset(r_env, r_check);
        }
    }
    return (data);
}

char **cpy_unset(char **env, int line)
{
    int i;
	int j;
    int k;
	char **r_env;

	i = -1;
    k = 0;
	while (env[++i] != NULL)
		;
	r_env = malloc(sizeof(char *) * i);
    i = 0;
	while (env[i] != NULL)
	{
		j = -1;
		r_env[k] = malloc(sizeof(char *) * ft_strlen(env[i]) + 1);
		while (env[i][++j] != '\0' && i != line)
			r_env[k][j] = env[i][j];
        if (i != line)
            k++;
        i++;
	}
	r_env[k] = NULL;
	return (r_env);
}

char    **unset_dup(char **env, char *var)
{
    int     r_check;
    char    **r_env;

    r_check = check_env_var(env, var);
    r_env = cpy_unset(env, r_check);
    return (r_env);
}