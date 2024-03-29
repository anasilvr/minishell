/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:01:00 by jgagnon           #+#    #+#             */
/*   Updated: 2023/04/19 15:29:09 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_dollar(char *line, char **env, int *i, int err)
{
	char	*r_var;

	r_var = NULL;
	while (line[*i] == '$' && line[*i + 1] == '$')
		*i += 2;
	if (line[*i] == '$')
	{
		if (ft_isspace(line[++(*i)]) == 0 || line[*i] == '\''
			|| line[*i] == '"' || line[*i] == '\0')
			return (ft_strdup("$"));
		r_var = quotes_handler(line, env, i, err);
		if (line[*i] == '?')
		{
			(*i) += 1;
			return (ft_itoa(err));
		}
		else if (ft_isdigit(line[*i]) != 1)
			r_var = dollar_env_handler(line, env, i);
		else if (ft_isdigit(line[*i]) == 1)
			(*i) += 1;
	}
	return (r_var);
}

char	*expand_token(char *token, t_data *data, int *i)
{
	char	*r_var;

	r_var = NULL;
	if (token[*i] == '$')
	{
		r_var = expand_dollar(token, data->envp_cp, i, data->exit_code);
		data->treat = true;
	}
	else if (token[*i] == '\'' || token[*i] == '"')
	{
		r_var = quotes_handler(token, data->envp_cp, i, data->exit_code);
		data->treat = true;
	}
	return (r_var);
}

char	*dollar_env_handler(char *line, char **env, int *i)
{
	char	*r_var;
	int		j;

	j = 0;
	r_var = NULL;
	while ((ft_isalnum(line[*i + j]) == 1 && line[*i + j] != '\0'))
		j++;
	r_var = cpy_env_var(env, ft_substr(line, *i, j));
	(*i) += j;
	return (r_var);
}

t_tok	*token_token_changr(t_data *data, char *r_line, t_tok **keep_first_node)
{
	if (r_line == NULL)
	{
		data->token = delmidnode_toklist(data->token);
		*keep_first_node = data->token;
	}
	else if (r_line != NULL)
	{
		data->token->token = xfree(data->token->token);
		data->token->token = ft_strdup(r_line);
		r_line = xfree(r_line);
		if (data->token->type == INVALID)
			data->token = delmidnode_toklist(data->token);
		if (data->token)
			data->token = data->token->next;
	}
	return (data->token);
}
