#include "minishell.h"

char **new_pwd(char **env)
{
    int i;
    int j;
    char *n_path;

    n_path = NULL;
    j = -1;
    env = unset_dup(env, "PWD");
    env = cpy_env(env, 1);
    n_path = ft_strjoin("PWD=", getcwd(n_path, ft_strlen(getcwd(NULL, 0))));
    while (env[++j] != NULL)
        ;
    free(env[j]);
    env[j] = malloc(sizeof(char) * ft_strlen(n_path) + 1);
    i = -1;
    while (n_path[++i] != '\0')
        env[j][i] = n_path[i];
    env[j][i] = '\0';
    env[++j] = NULL;
    free(n_path);
    return(env);
}

char **cd_handler(char **instruct, char **env)
{
    int     i;
    int     j;
    char    *n_path;

    i = 0;
    j = -1;
    n_path = NULL;
    if (ft_cmp_builtin(instruct[i], "cd", 2) == 0)
    {
        env = update_oldpwd(env);
        if (chdir(instruct[++i]) == 0)
            env = new_pwd(env);
    }
    return(env);
}

char **update_oldpwd(char **env)
{
    char    *n_path;
    int     i;
    int     j;

    n_path = NULL;
    i = -1;
    j = -1;
    env = unset_dup(env, "OLDPWD");
    env = cpy_env(env, 1);
    n_path = ft_strjoin("OLDPWD=", getcwd(n_path, ft_strlen(getcwd(NULL, 0))));
    while (env[++i] != NULL)
        ;
    free(env[i]);
    env[i] = malloc(sizeof(char) * ft_strlen(n_path) + 1);
    j = -1;
    while (n_path[++j] != '\0')
        env[i][j] = n_path[j];
    env[i][j] = '\0';
    env[++i] = NULL;
    return (env);
}