/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:55:35 by jgagnon           #+#    #+#             */
/*   Updated: 2023/04/21 10:59:37 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*charjoinfree(const char *s1, const char c)
{
	char		*r_str;
	size_t		len;
	int			i;

	len = 0;
	if (s1)
		len = ft_strlen(s1);
	i = -1;
	r_str = NULL;
	if (len < 1)
	{
		r_str = ft_calloc(2, sizeof(char));
		r_str[0] = c;
		r_str[1] = '\0';
	}
	else if (len > 0)
	{
		r_str = ft_calloc((len + 2), sizeof(char));
		while (s1[++i] != '\0')
			r_str[i] = s1[i];
		r_str[i] = c;
		r_str[i + 1] = '\0';
	}
	xfree((char *) s1);
	return (r_str);
}

static char	*add_line(char *r_var, char *r_line)
{
	if (r_line == NULL)
		r_line = ft_strdup(r_var);
	else if (r_line != NULL)
		r_line = ft_strjoin_free(r_line, r_var);
	return (r_line);
}

static char	*token_handler(t_tok *node, t_data *data)
{
	char	*r_line;
	char	*r_var;
	int		i;

	i = 0;
	r_var = NULL;
	r_line = NULL;
	while (node->token[i] != '\0')
	{
		if (node->prev && node->prev->type == 3)
			;
		r_var = expand_token(node->token, data, &i);
		if (r_var != NULL)
			r_line = add_line(r_var, r_line);
		else if (r_var == NULL && node->token[i] != '\0'\
			&& data->treat == false)
			r_line = charjoinfree(r_line, node->token[i++]);
		if (r_var != NULL)
			r_var = xfree(r_var);
		data->treat = false;
	}
	if (r_line == NULL)
		node->type = INVALID;
	return (r_line);
}

void	treat_line(t_data *data)
{
	int		i;
	char	*r_line;
	t_tok	*keep_first_node;

	r_line = NULL;
	keep_first_node = data->token;
	while (data->token != NULL)
	{
		i = 0;
		if (data->token->type == 1 || data->token->type == 8 || \
			data->token->type == 10)
			r_line = token_handler(data->token, data);
		if (data->token->type == 1 || (data->token->type >= 8 && \
			data->token->type <= 11))
			data->token = token_token_changr(data, r_line, &keep_first_node);
		else
			data->token = data->token->next;
	}
	data->token = keep_first_node;
}

char	*rl_gets(void)
{
	char	*line;
	char	*r_line;

	line = (char *) NULL;
	line = readline("WTS$ ");
	if (line && *line)
		add_history(line);
	r_line = ft_strdup(line);
	xfree(line);
	return (r_line);
}
