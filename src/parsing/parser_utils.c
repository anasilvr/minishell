#include "../../include/minishell.h"

int	cmd_len(char *str, int len)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	printf("Setting cmd length\n");
	while (i < len)
	{
		if (is_set(str[i], QUOTES))
			i += (length_til_match(&str[i], str[i]));
		if (is_set(str[i], METACHAR))
		{
			if (str[i] == '<' && str[i + 1] == '<')
			{
				i += 2;
				while (ft_isset(str[i], WHITESPACE))
					i++;
				i += (1 + length_til_match(&str[i], ' '));
				printf(" i = %d\n", i);
			}
			break ;
		}	
		i++;
	}
	return (i);
}

t_cmd	*create_cmdlist(t_data *data)
{
	size_t		len;
	t_cmd		*cmdlst;
	char		*str;

	len = 0;
	cmdlst = NULL;
	str = data->input;
	skip_whitespaces(&str);
	while (*str)
	{
		len = cmd_len(str, ft_strlen(str));
		addback_cmdline(&cmdlst, new_cmdline(ft_substr(str, 0, len)));
		data->nb_cmds++;
		str += (len);
		skip_whitespaces(&str);
		skip_meta(&str);
	}
	free_cmdlist(data->cmd_lst);
	return (cmdlst);
}

t_cmd	*new_cmdline(char *line)
{
	t_cmd	*new;

	new = (t_cmd *)ft_xcalloc(sizeof(*new));
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