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

	len = 0;
	cmdlst = NULL;
	str = data->input;
	while (*str)
	{
		skip_whitespaces(&str);
		len = cmd_len(str, ft_strlen(str));
		addback_cmdline(&cmdlst, new_cmdline(ft_substr(str, 0, len)));
		data->nb_pipes++;
		str += (len);
		skip_whitespaces(&str);
		skip_meta(&str);
	}
	free_cmdlist(data->cmd_lst);
	return (cmdlst);
}

int	first_word_len(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] != '\0' && str[i] != ' ') // Voir a ajouter si besoin d<autre whitespaces
	{
		len++;
		i++;
	}
	return (i);
}

int	redirect_creation(char *line, int *i)
{
	char	*redirect_filename;
	int		filename_len;
	int		fd;

	filename_len = first_word_len(line[(*i)]);
	redirect_filename = ft_substr(line[(*i)], 0, filename_len);
	fd = open_to_readwrite(redirect_filename, O_TRUNC);
	(*i) += filename_len;
	return (fd);
}

int	redirect_parsing(char *line)
{
	int		i;
	int		*file_fd[2]; //0 == fdin, 1 == fdout

	i = 0;
	while(line[i] != '\0')
	{
		if (line[i++] == '>')
		{
			if (line[i] == ' ')
				i++;
			redirect_creation(line, &i);
			// A PARTIR DICI JAI PASSE TOUT LA REDIRECTION
		}
		else if(line[i++] == '>>')
		{
			if (line[i] == ' ')
				i++;
			filename_len = first_word_len(line[i]);
			redirect_filename = ft_substr(line[i], 0, filename_len);
			file_fd[1] = open_to_read(redirect_filename, O_APPEND);
			i += filename_len;
			// A PARTIR DICI JAI PASSE TOUT LA REDIRECTION
		}
		else if(line[i++] == '<')
		{
			if (line[i] == ' ')
				i++;
			filename_len = first_word_len(line[i]);
			redirect_filename = ft_substr(line[i], 0, filename_len);
			file_fd[1] = open_to_read(redirect_filename, NULL);
			i += filename_len;
			// A PARTIR DICI JAI PASSE TOUT LA REDIRECTION
		}
		else
			i++;
	}
}


//good , but long
// int	redirect_parsing(char *line)
// {
// 	int		i;
// 	char	*redirect_filename;
// 	int		filename_len;
// 	int		*file_fd[2]; //0 == fdin, 1 == fdout

// 	i = 0;
// 	while(line[i] != '\0')
// 	{
// 		if (line[i] == '>')
// 		{
// 			i++;
// 			if (line[i] == ' ')
// 				i++;
// 			filename_len = first_word_len(line[i]);
// 			redirect_filename = ft_substr(line[i], 0, filename_len);
// 			file_fd[1] = open_to_readwrite(redirect_filename, O_TRUNC);
// 			i += filename_len;
// 			// A PARTIR DICI JAI PASSE TOUT LA REDIRECTION
// 		}
// 		else if(line[i] == '>>')
// 		{
// 			i++;
// 			if (line[i] == ' ')
// 				i++;
// 			filename_len = first_word_len(line[i]);
// 			redirect_filename = ft_substr(line[i], 0, filename_len);
// 			file_fd[1] = open_to_read(redirect_filename, O_APPEND);
// 			i += filename_len;
// 			// A PARTIR DICI JAI PASSE TOUT LA REDIRECTION
// 		}
// 		else if(line[i] == '<')
// 		{
// 			i++;
// 			if (line[i] == ' ')
// 				i++;
// 			filename_len = first_word_len(line[i]);
// 			redirect_filename = ft_substr(line[i], 0, filename_len);
// 			file_fd[1] = open_to_read(redirect_filename, NULL);
// 			i += filename_len;
// 			// A PARTIR DICI JAI PASSE TOUT LA REDIRECTION
// 		}
// 		else
// 			i++;
// 	}
// }

t_cmd	*new_cmdline(char *line)
{
	t_cmd	*new;

	new = ft_xcalloc(1, sizeof(t_cmd));
	redirect_parsing(line);
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
