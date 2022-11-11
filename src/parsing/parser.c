#include "../../include/minishell.h"

char	*get_cmdline(t_tok **toklist);
t_cmd	*new_cmdline(char *line);
void	addback_cmdline(t_cmd **cmdlist, t_cmd *line);
t_cmd	*get_lastcmd(t_cmd *node);
char	*get_singlecmd(t_tok **toklist);

t_cmd 	*parser(t_data *data)
{
	t_tok	*tok;
	t_cmd	*cmd;
	char	*line;

	tok = data->token;
	if (!tok)
		return (0);
	cmd = NULL;
//	print_cmdlines(cmd);
	while (tok && data->nb_pipes > 0)
	{
		line = get_cmdline(&tok);
		addback_cmdline(&cmd, new_cmdline(line));
		data->nb_pipes--;
	//	xfree(line);
	}
	if (data->nb_pipes == 0)
	{
		line = get_singlecmd(&tok);
		addback_cmdline(&cmd, new_cmdline(line));
	//	xfree(line);
	}
	print_cmdlines(cmd);
	return (cmd);
}

char	*get_singlecmd(t_tok **toklist)
{
	t_tok	*current;
	char	*line;

	if (*toklist)
	{
		current = *toklist;
		line = ft_strdup("");
		while (current && current->token)
		{
			line = ft_strjoin_free(line, current->token);
			line = ft_strjoin_free(line, " ");
			current = current->next;
		}
		return (line);
	}
	return (NULL);
}

char	*get_cmdline(t_tok **toklist)
{
	t_tok	*current;
	char	*line;

	if (*toklist)
	{
		current = *toklist;
		line = ft_strdup("");
		while (current && current->type != PIPE)
		{
			line = ft_strjoin_free(line, current->token);
			line = ft_strjoin_free(line, " ");
			*current = *current->next;
		}
		if (current->type == PIPE)
		{
			line = ft_strjoin_free(line, current->token);
			*current = *current->next;
		}
		return (line);
	}
	return (NULL);
}

//add flags to set expand and heredoc booleans (char *line, bool expand, bool heredoc)
//could also be something to help with fds?
t_cmd	*new_cmdline(char *line)
{
	t_cmd	*new;

	new = (t_cmd *)ft_xcalloc(sizeof(*new));
	new->prev = NULL;
	new->cmdline = ft_strdup(line);
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
	printf("returning: %s\n", node->cmdline);
	return (node);
}
