#include "minishell.h"

char    **add_var(char **env, char *n_var)
{
    int     i;
    int     j;
    char    **r_env;

    j = -1;
    i = -1;
    r_env = cpy_env(env, 1);
    while (env[++i] != NULL)
        ;
    free(r_env[i]);
    r_env[i] = malloc(sizeof(char) * (ft_strlen(n_var) + 1));
    while (n_var[++j] != '\0')
        r_env[i][j] = n_var[j];
    r_env[i][j] = '\0';
    i++;
    r_env[i] = NULL;
    free_tab(env);
    return (r_env);
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

    i = 0;
    if (ft_cmp_builtin(instruct[i], "export", 6) == 0)
    {
        while (instruct[++i] != NULL)
        {
            if (export_pars(instruct[i], data->envp_cp) == -1)
                data->envp_cp = add_var(data->envp_cp, instruct[i]);
            else if (export_pars(instruct[i], data->envp_cp) >= 0)
            {
                data->envp_cp = unset_dup(data->envp_cp, var_trim(instruct[i]));
                data->envp_cp = add_var(data->envp_cp, instruct[i]);
            }
        }
    }
    return (data);
}
