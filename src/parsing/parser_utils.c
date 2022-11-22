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
			i += length_til_match(&str[i], str[i]);
		if (is_set(str[i], METACHAR))
			return (i);
		i++;
	}
	return (i);
}

t_cmd	*create_cmdlist(t_data *data)
{
	int		len;
	t_cmd	*cmdlst;
	char *str;

	len = 0;
	cmdlst = NULL;
	str = data->input;
	skip_whitespaces(&str);
	while (*str)
	{
		len = cmd_len(str, ft_strlen(str));
		addback_cmdline(&cmdlst, new_cmdline(ft_substr(str, 0, len)));
		data->nb_cmds++;
		str += (len + 1);
		skip_whitespaces(&str);
	}
	return (cmdlst);
}

t_cmd	*new_cmdline(char *line)
{
	t_cmd	*new;

	new = (t_cmd *)ft_xcalloc(sizeof(*new));
	new->prev = NULL;
	new->cmdline = ft_strdup(line);
	new->next = NULL;
	xfree(line);
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