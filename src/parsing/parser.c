#include "../../include/minishell.h"

char	*get_cmdline(t_tok **toklist);
t_cmd	*new_cmdline(char *line);
void	addback_cmdline(t_cmd **cmdlist, t_cmd *line);
t_cmd	*get_lastcmd(t_cmd *node);
char	*get_singlecmd(t_tok **toklist);

static void	print_cmdlines(t_cmd *list)
{
	t_cmd	*node;
	int		i;

	node = list;
	i = 0;
	while (node)
	{
		if (!node)
			return ;
		printf("cmdline[%d] = %s\n", i, node->cmdline);
		node = node->next;
		i++;
	}
}

int	parser(t_data *data)
{
	t_tok	*tok;
	t_cmd	*cmd;
	char	*line;

	tok = data->token;
	if (!tok)
		return (0);
	cmd = data->cmd_lst;
	while (tok && data->nb_pipes > 0)
	{
		printf("\t\t\t\t\tGetting here :)\n");
		line = get_cmdline(&tok);
		addback_cmdline(&cmd, new_cmdline(line));
		data->nb_pipes--;
		free(line);
	}
	if (data->nb_pipes == 0)
	{
		line = get_singlecmd(&tok);
		addback_cmdline(&cmd, new_cmdline(line));
		free(line);
	}
	print_cmdlines(cmd);
	return (g_status);
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

t_cmd	*new_cmdline(char *line)
{
	t_cmd	*new;

	new = (t_cmd *)ft_xcalloc(sizeof(*new));
	new->prev = NULL;
	new->next = NULL;
	new->cmdline = ft_strdup(line);
	return (new);
}

void	addback_cmdline(t_cmd **cmdlist, t_cmd *line)
{
	printf ("line received at addback: %s\n", line->cmdline);
	t_cmd	*tmp;

	if (!line)
		return ;
	if (!*cmdlist)
	{
		*cmdlist = line;
		return ;
	}
	tmp = get_lastcmd(*cmdlist);
	tmp->next = line;
	printf ("line returned at addback: %s\n", line->cmdline);
}

t_cmd	*get_lastcmd(t_cmd *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}
