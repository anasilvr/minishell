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

char	*expand_token(char *token, char **env, int *i, int err, bool *treat)
{
	char *r_var;

	r_var = NULL;
	if (token[*i] == '$')
	{
		r_var = expand_dollar(token, env, i, err);
		*treat = true;
	}
	else if (token[*i] == '\'' || token[*i] == '"')
	{
		r_var = quotes_handler(token, env, i, err);
		*treat = true;
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
