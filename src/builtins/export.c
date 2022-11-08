#include "minishell.h"

int env_dup(char *n_var, char **env)
{
    int i;
    int j;

    i = -1;
    j = 0;
    while (env[j] != NULL)
    {
        while (n_var[++i] != '=' && n_var[i] == env[j][i])
            ;
        if (n_var[i] != '=' && env[j][i] != '=')
        {
            i = -1;
            j++;
        }
        else if (n_var[i] == '=' && env[j][i] == '=')
            return (1);
    }
    return (0);
}

int export_pars(char *n_var, char **env)
{
    int i;
    int j;

    i = 0;
    while (n_var[i] != '=' && n_var[i] != '\0')
        i++;
    if (n_var[i] == '=')
    {
        j = -1;
        while (env[++j] != NULL)
            if (env_dup(n_var, env) != 0)
                return (1);
        return (0);
    }
    return (1);
}

// Faire le check dup pour éviter d'avoir 2 fois la même variable

char **export_handler(char **instruct, char **env)
{
    int     i;
    int     j;
    int     k;
    char    **r_env;

    i = 0;
    r_env = env;
    if (ft_cmp_builtin(instruct[i], "export", 6) == 0)
    {
        while (instruct[++i] != NULL)
        {
            j = -1;
            if (export_pars(instruct[i], env) == 0)
            {
                r_env = cpy_env(r_env, 1);
                while (r_env[++j] != NULL)
                    ;
                free(r_env[j]);
                r_env[j] = malloc(sizeof(char) * (ft_strlen(instruct[i]) + 1));
                k = -1;
                while (instruct[i][++k] != '\0')
                    r_env[j][k] = instruct[i][k];
                r_env[j][k] = '\0';
                j++;
                r_env[j] = NULL;
            }
        }
    }
    return (r_env);
}
