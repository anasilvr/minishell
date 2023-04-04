/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:56:37 by tchalifo          #+#    #+#             */
/*   Updated: 2023/04/03 15:15:14 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*dollard_env_finder(char **env, char *r_quotes)
{
	char	*r_env;
	char    *r_line;
	int		i;
	
	r_line = NULL;
	i = 0;
	while (r_quotes[i] != '\0')
	{
		r_env = dollar_handler(r_quotes, env, &i);
		if (r_env != NULL && r_line == NULL)
			r_line = ft_strdup(r_env);
		else if (r_env != NULL && r_line != NULL)
			r_line = ft_strjoin_free(r_line, r_env);
		if (r_env == NULL && r_quotes[i] != '\0')
		{
			r_line = charjoinfree(r_line, r_quotes[i]);
			i++;
		}
		r_env = xfree(r_env);
	}
	return (r_line);
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
	r_line = NULL;
	len = quotes_len(line, j, '"');
	if (len == 0)
		return (r_env);
	else if (len > 0)
	{
		r_quotes = ft_calloc(sizeof(char) , (len + 1));
		while (len > ++i)
			r_quotes[i] = line[*j + i];
		*j += len + 1;
	}
	r_line = dollard_env_finder(env, r_quotes);
	xfree(r_quotes);
	return (r_line);
}

char *single_quotes_handler(char *line, int* j)
{
	int		i;
	int		len;
	char	*r_val;

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
	}
	return (r_val);
}

char    *dollar_handler(char *line, char **env, int* j)
{
    int     i;
    char    *r_var;

    i = 0;
    r_var = NULL;
    while (line[*j] == '$' && line[*j + 1] == '$')
        *j += 2;
    if (line[*j] == '$' && (ft_isspace(line[*j + 1]) == 0 || line[*j + 1] != '\0'))
    {
        if (line[++(*j)] == '\'')
            r_var = single_quotes_handler(line, j);
        else if (line[*j] == '"')
            r_var = double_quote_handler(line, env, j);
        else if (line[*j] == '?')
            r_var = ft_itoa(g_status);
        else
        {
            while (ft_isalnum(line[*j + i]) == 1 && line[*j + i] != '\0')
                i++;
            r_var = cpy_env_var(env, ft_substr(line, *j, i));
        }
        (*j) += i;
    }
    return (r_var);
}

char	*cpy_env_var(char **env, char *var)
{
	int		i;
	int		j;
	int		k;
	char	*r_var;

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
	xfree(var);
	return (r_var);
}
