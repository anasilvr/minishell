#include "minishell.h"

char    **add_var(char **env, char *n_var)
{
    int i;
    int j;

    j = -1;
    i = -1;
    env = cpy_env(env, 1);
    while (env[++i] != NULL)
        ;
    free(env[i]);
    env[i] = malloc(sizeof(char) * (ft_strlen(n_var) + 1));
    while (n_var[++j] != '\0')
        env[i][j] = n_var[j];
    env[i][j] = '\0';
    i++;
    env[i] = NULL;
    return (env);
}

char    *var_trim(char *n_var)
{
    int     i;
    char    *r_var;

    i = -1;
    while (n_var[++i] != '=')
        ;
    r_var = malloc(sizeof(char) * (i + 1));
    i= -1;
    while (n_var[++i] != '=')
        r_var[i] = n_var[i];
    r_var[i] = '\0';
    free(n_var);
    return (r_var);
}

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
            return (j);
    }
    return (-1);
}

int export_pars(char *n_var, char **env)
{
    int i;

    i = 0;
    while (n_var[i] != '=' && n_var[i] != '\0')
        i++;
    if (n_var[i] == '=')
        return (env_dup(n_var, env));
    return (-2);
}

t_data *export_handler(char **instruct, t_data *data)
{
    int     i;
    char    **r_env;

    i = 0;
    r_env = data->envp_cp;
    if (ft_cmp_builtin(instruct[i], "export", 6) == 0)
    {
        while (instruct[++i] != NULL)
        {
            if (export_pars(instruct[i], r_env) == -1)
                r_env = add_var(r_env, instruct[i]);
            else if (export_pars(instruct[i], r_env) >= 0)
            {
                r_env = unset_dup(r_env, var_trim(instruct[i]));
                r_env = add_var(r_env, instruct[i]);
            }
        }
    }
    return (data);
}
