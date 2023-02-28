#include "../../include/minishell.h"

int	space_handler(char *str, int i)
{
    int	j;

    j = i;
    while (ft_isspace(str[i]) == 0 && str[i] != '\0')
        i++;
    if (str[i] == '\0')
        return (i - 1);
    return (j);
}

char *double_quote_handler(char *line, char **env, int* j)
{
    int     i;
    int     len;
    char    *r_quotes;
	char	*r_env;
    char    *r_line;

    i = -1;
    len = 0;
	r_env = NULL;
    r_quotes = NULL;
    r_line = ft_calloc(1, sizeof(char));
    len = quotes_len(line, j, '"');
    if (len == 0)
        return (r_env);
    else if (len > 0)
    {
        r_quotes = malloc(sizeof(char) * (len + 1));
        while (len > ++i)
            r_quotes[i] = line[*j + i];
        *j += len + 1;
        r_quotes[i + 1] = '\0';
    }
	i = -1;
	while (r_quotes[++i] != '\0')
	{
    	r_env = dollar_handler(r_quotes, env, &i);
		if (r_env != NULL)
			r_line = ft_strjoin(r_line, r_env);
		xfree(r_env);
		if (r_env == NULL)
            r_line = charjoinfree(r_line, r_quotes[i]);
	}
    return (r_line);
}

char *single_quotes_handler(char *line, int* j)
{
    int     i;
    int     len;
    char    *r_val;

    i = -1;
    len = quotes_len(line, j, '\'');
    r_val = NULL;
    if (len == 0)
        return (r_val);
    else if (len > 0)
    {
        r_val = ft_calloc((len + 1), sizeof(char));
        while (len > ++i)
            r_val[i] = line[*j + i];
        *j += len + 1;
        r_val[i + 1] = '\0';
    }
    return (r_val);
}

char    *dollar_handler(char *line, char **env, int* j)
{
    int i;
    char *r_var;

    i = 0;
    r_var = NULL;
    while (line[*j] == '$' && line[*j + 1] == '$')
		*j += 2;
    if (line[*j] == '$' && line[*j + 1] == '\'')
    {
        *j += 1;
        r_var = single_quotes_handler(line, j);
    }
    else if (line[*j] == '$' && line[*j + 1] == '"')
    {
        *j += 1;
        r_var = double_quote_handler(line, env, j);
		*j += 1;
		r_var = charjoinfree(r_var, 0x20);
    }
    else if (line[*j] == '$' && (ft_isspace(line[*j + 1]) == 0 || line[*j + 1] == '\0'))
    {
        r_var = ft_strdup("$");
        *j += 1;
    }
    else if (line[*j] == '$')
    {
        *j += 1;
        while (ft_isspace(line[*j + i]) != 0 && line[*j + i] != '\0' && line[*j + i] != '"' && line[*j + i] != '$')
            i++;
        r_var = ft_substr(line, *j, i);
        r_var = cpy_env_var(env, r_var);
        *j += i;
    }
    return (r_var);
}

char	*cpy_env_var(char **env, char *var)
{
    int		i;
    int		j;
    int     k;
    char    *r_var;

    i = -1;
    j = -1;
    k = -1;
    r_var = NULL;
    while (env[++i] != NULL)
    {
        if (ft_cmp_env(env[i], var, (ft_strlen(var))) == 0)
            break ;
    }
    if (env[i] != NULL)
    {
        while (env[i][++j] != '=')
            ;
        r_var = malloc(sizeof(char) * (ft_strlen(&env[i][j])));
        while (env[i][++j] != '\0')
            r_var[++k] = env[i][j];
		r_var[++k] = '\0';
    }
    return (r_var);
}