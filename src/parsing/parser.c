#include "../../include/minishell.h"

char	*get_cmdline(t_tok **toklist, t_type *io);
t_cmd	*new_cmdline(char *line);
void	addback_cmdline(t_cmd **cmdlist, t_cmd *line, t_type *io);
t_cmd	*get_lastcmd(t_cmd *node);

void	parser(t_data *data)
{
	t_cmd	*cmd;
	char	*line;
	t_type	*io;

	if (!data->token)
		return ;
	cmd = NULL;
	io = ft_xcalloc(sizeof(t_type));
	while (data->token)
	{
		line = get_cmdline(&data->token, io);
		addback_cmdline(&cmd, new_cmdline(line), io);
		printf("\t\t\tGetting here too [%u]!", cmd->io_flag);
		*io = 0;
		xfree(line);
	}
	data->cmd_lst = cmd;
	xfree(io);
}

char	*get_cmdline(t_tok **toklist, t_type *io)
{
	t_tok	*current;
	char	*line;

	if (*toklist)
	{
		current = *toklist;
		line = ft_strdup("");
		while (current && current->token)
		{
			if (current->type >= 2 && current->type <= 6)
			{
				*io = current->type;
				current = current->next;
				*toklist = current;
				return (line);
			}
			line = ft_strjoin_free(line, current->token);
			line = ft_strjoin_free(line, " ");
			current = current->next;
			*toklist = current;
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

void	addback_cmdline(t_cmd **cmdlist, t_cmd *line, t_type *io)
{
	t_cmd	*tmp;

	if (!line)
		return ;
	tmp = NULL;
	line->io_flag = *io;
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
