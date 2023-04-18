/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:56:37 by tchalifo          #+#    #+#             */
/*   Updated: 2023/04/04 16:30:51 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*dollar_env_finder(char **env, char *r_quotes, int err_code)
{
	char	*r_env;
	char	*r_line;
	int		i;

	r_line = NULL;
	i = 0;
	while (r_quotes[i] != '\0')
	{
		r_env = expand_dollar(r_quotes, env, &i, err_code);
		if (r_env != NULL && r_line == NULL)
			r_line = ft_strdup(r_env);
		else if (r_env != NULL && r_line != NULL)
			r_line = ft_strjoin_free(r_line, r_env);
		if (r_env == NULL && (r_quotes[i] != '\0'))
		{
			r_line = charjoinfree(r_line, r_quotes[i]);
			i++;
		}
		r_env = xfree(r_env);
	}
	return (r_line);
}

char	*double_quote_handler(char *line, char **env, int *j, int err_code)
{
	int		i;
	int		len;
	char	*r_quotes;
	char	*r_line;

	i = -1;
	len = 0;
	r_quotes = NULL;
	r_line = NULL;
	len = quotes_len(line, j, '"');
	if (len == 0)
		return (NULL);
	else if (len > 0)
	{
		r_quotes = ft_calloc(sizeof(char), (len + 1));
		while (len > ++i)
			r_quotes[i] = line[*j + i];
		*j += len + 1;
	}
	r_line = dollar_env_finder(env, r_quotes, err_code);
	xfree(r_quotes);
	return (r_line);
}

char	*single_quotes_handler(char *line, int *j)
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

char	*quotes_handler(char *line, char **env, int *j, int err_code)
{
	char	*r_var;

	r_var = NULL;
	if (line[(*j)] == '\'')
		r_var = single_quotes_handler(line, j);
	else if (line[*j] == '"')
		r_var = double_quote_handler(line, env, j, err_code);
	return (r_var);
}

char	*dollar_handler(char *line, char **env, int *j, int err_code)
{
	int		i;
	char	*r_var;

	i = 0;
	r_var = NULL;
	while (line[*j] == '$' && line[*j + 1] == '$')
		*j += 2;
	if (line[*j] == '$' && (ft_isspace(line[++(*j)]) == 0 || \
		line[*j] != '\0'))
	{
		r_var = quotes_handler(line, env, j, err_code);
		if (line[*j] == '?')
		{
			(*j)++;
			r_var = ft_itoa(err_code);
		}
		else if (r_var == NULL && ft_isdigit(line[*j]) != 1)
		{
			while ((ft_isalnum(line[*j + i]) == 1 && line[*j + i] != '\0'))
				i++;
			r_var = cpy_env_var(env, ft_substr(line, *j, i));
			(*j) += i;
		}
		else if (r_var == NULL && ft_isdigit(line[*j]) == 1)
			(*j) += 1;
	}
	return (r_var);
}
