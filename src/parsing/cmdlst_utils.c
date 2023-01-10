#include "../../include/minishell.h"

t_cmd	*new_cmdline(char *line)
{
	t_cmd	*new;

	new = ft_xcalloc(1, sizeof(t_cmd));
	new->filefd[0] = -2;
	new->filefd[1] = -2;
	new->pipefd[0] = -2;
	new->pipefd[1] = -2;
	new->fork_pid = -2;
	new->err = -2;
	new->prev = NULL;
	new->cmdline = line;
	new->next = NULL;
	return (new);
}

void	addback_cmdline(t_cmd **cmdlist, t_cmd *line)
{
	t_cmd	*tmp;

	if (!line)
		return ;
	tmp = NULL;
	if (*cmdlist && (*cmdlist)->cmdline)
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
