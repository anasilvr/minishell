/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:47:35 by tchalifo          #+#    #+#             */
/*   Updated: 2023/04/04 16:32:46 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*heredoc_dollar(int *i, char **env, char *line)
{
	char	*r_line;
	char	*r_var;
	char	*r_status;

	r_var = NULL;
	r_line = NULL;
	r_status = ft_itoa(g_status);
	if (line[++(*i)] == '$')
		;
	else if (line[(*i)] == '?')
		r_line = ft_strjoin_free(r_line, r_status);
	else if (line[--(*i)] == '$')
	{
		while (ft_isalnum(line[++(*i)]) == 1)
			r_var = charjoinfree(r_var, line[(*i)]);
		r_var = cpy_env_var(env, r_var);
		if (r_line == NULL)
			r_line = ft_strdup(r_var);
		else
			r_line = ft_strjoin_free(r_line, r_var);
		r_var = xfree(r_var);
	}
	xfree(r_status);
	return (r_line);
}

char	*heredoc_special_handling(char **env, char *line)
{
	int		i;
	char	*r_line;
	char	*r_dollar;

	i = 0;
	r_line = NULL;
	r_dollar = NULL;
	while (line [i] != '\0')
	{
		if (line[i] == '$')
		{
			r_dollar = heredoc_dollar(&i, env, line);
			if (r_dollar != NULL && r_line == NULL)
				r_line = ft_strdup(r_dollar);
			else if (r_dollar != NULL)
				r_line = ft_strjoin_free(r_line, r_dollar);
			r_dollar = xfree(r_dollar);
		}
		else
			r_line = charjoinfree(r_line, line[i++]);
	}
	return (r_line);
}

char	*trim_delim(const char *delim)
{
	int		i;
	int		j;
	char	*r_delim;
	char	quote;

	i = 0;
	j = -1;
	r_delim = NULL;
	if (delim[i] == '"' || delim[i] == '\'')
	{
		quote = delim[i];
		while (delim[++i] != quote)
			;
		r_delim = malloc(sizeof(char) * i);
		i = 0;
		while (delim[++i] != quote)
			r_delim[++j] = delim[i];
		r_delim[++j] = '\0';
		return (r_delim);
	}
	return (ft_strdup(delim));
}

void	hd_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 4;
	}	
}
