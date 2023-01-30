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
		// heredoc parsing is segfaulting
	//	data->hd_struct = heredoc_parsing(ft_substr(str, 0, len));
		line = ft_substr(str, 0, len);
		addback_cmdline(&cmdlst, new_cmdline(line));
		str += (len);
		skip_whitespaces(&str);
		skip_meta(&str);
	}
	free_cmdlist(data->cmd_lst);
	return (cmdlst);
}

int	cmdline_redirlen(char *line, int i)
{
	int		redir_len;

	redir_len = 0;
	if (line[++i] == '>' || line[i + 1] == '>')
	{
		redir_len++;
		i++;
	}
	else if (line[i] == '<' || line[i + 1] == '<')
	{
		redir_len++;
		i++;
	}
	while (line[i] != '\0' && line[i] == ' ')
	{
		redir_len++;
		i++;
	}
	while (line[i] != '\0' && line[i] != ' ')
	{
		redir_len++;
		i++;
	}
	return (redir_len);

}

char	*cmdline_purged_cpy(char *line, int new_line_len)
{
	int		i;
	int		j;
	char	*new_cmdline;

	i = 0;
	j = 0;
	new_cmdline = ft_xcalloc(new_line_len + 1, sizeof(char *));
	while (line[i] != '\0')
	{
		if (line[i] == '>' || line[i] == '<')
		{
			i++;
			if (line[i - 1] == '<' && line[i] == '<')
				i++;
			else if (line[i - 1] == '>' && line[i] == '>')
				i++;
			while (line[i] != '\0' && line[i] == ' ')
				i++;
			while (line[i] != '\0' && line[i] != ' ')
				i++;
		}
		new_cmdline[j] = line[i];
		j++;
		i++;
	}
	new_cmdline[j] = '\0';
	free(line);
	return (new_cmdline);
}

char	*cmdline_redir_drop(char *line)
{
	int		i;
	int		line_len;
	int		redir_len;
	int		new_cmdline_len;

	line_len = ft_strlen(line);
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '>' || (line[i] == '>' && line[i + 1] == '>') 
			|| line[i] == '<'
				 || (line[i] == '<' && line[i + 1] == '<'))
		{
			i++;
			redir_len = cmdline_redirlen(line, i);
			new_cmdline_len = line_len - redir_len;
			line = cmdline_purged_cpy(line, new_cmdline_len);
		}
		else
			i++;
	}
	return (line);
}

t_cmd	*new_cmdline(char *line)
{
	t_cmd	*new;

	new = ft_xcalloc(1, sizeof(t_cmd));
	new->filefd[0] = -2;
	new->filefd[1] = -2;
//	new->cmdline = ft_strdup(line);
	//here
	redirect_parsing(line, new->filefd);
	new->cmdline = cmdline_redir_drop(line);
	new->pipefd[0] = -2;
	new->pipefd[1] = -2;
	// new->fork_pid = -2;
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
