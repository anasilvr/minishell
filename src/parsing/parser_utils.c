/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:45:25 by tchalifo          #+#    #+#             */
/*   Updated: 2023/04/19 08:48:09 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cmd_len(char *str, int len)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (i < len)
	{
		if (is_set(str[i], QUOTES))
			i += (length_til_match(&str[i], str[i]));
		if (is_set(str[i], "|"))
			break ;
		i++;
	}
	return (i);
}

t_cmd	*create_cmdlist(t_data *data)
{
	size_t		len;
	t_cmd		*cmdlst;
	char		*str;
	char		*line;

	len = 0;
	cmdlst = NULL;
	str = data->input;
	line = NULL;
	while (*str)
	{
		len = cmd_len(str, ft_strlen(str));
		line = ft_substr(str, 0, len);
		addback_cmdline(&cmdlst, new_cmdline(line));
		xfree(line);
		str += (len);
		skip_whitespaces(&str);
		skip_meta(&str);
	}
	data->cmd_lst = free_cmdlist(data->cmd_lst);
	return (cmdlst);
}

t_cmd	*new_cmdline(char *line)
{
	t_cmd	*new;

	new = ft_xcalloc(1, sizeof(t_cmd));
	new->filefd[0] = -2;
	new->filefd[1] = -2;
	new->cmdline = ft_strdup(line);
	new->pipefd[0] = -2;
	new->pipefd[1] = -2;
	new->err = -2;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	addback_cmdline(t_cmd **cmdlist, t_cmd *line)
{
	t_cmd	*tmp;

	if (!line)
		return ;
	tmp = NULL;
	if (*cmdlist)
	{
		tmp = get_lastcmd(*cmdlist);
		tmp->next = line;
		line->prev = tmp;
		line->next = NULL;
	}
	else
		*cmdlist = line;
	return ;
}

t_cmd	*get_lastcmd(t_cmd *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}
