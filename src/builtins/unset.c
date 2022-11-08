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

char    **unset_handler(char **env, char *var)
{
    int     r_check;
    char    **r_env;

    if ((r_check = check_env_var(env, var)) != -1)
        printf("Variable trouvée! À la ligne : %d\n", r_check);
    r_env = cpy_unset(env, r_check);
    return (r_env);
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