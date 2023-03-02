#include "../../include/minishell.h"

t_hdoc	*write_heredoc(char *delimiter)
{
	char	*line;
	t_hdoc	*hd_struct;

	line = (char *) NULL;
	while (ft_strcmp(delimiter, line))
	{
		line = readline("> ");
		// Sans doute la meilleur endroit pour la gestion des $sign (expention)
		hd_struct = ft_dllst_add_back(hd_struct, line);
		if (line)
		{
			xfree(line);
			line = (char *) NULL;
		}
	}
	return (hd_struct);
}

int	heredoc_to_pipe(t_hdoc *hd_struct)

{
	int	hd_pipe_fd[2];
	int	hd_fork_pid;

	if (pipe(hd_pipe_fd) == -1)
	return (errno);
	hd_fork_pid = fork ();
	if (hd_fork_pid == -1)
	  return (errno);
	if (hd_fork_pid == 0)
	{
		while (hd_struct->next != NULL)
		{
			close(hd_pipe_fd[0]);
			ft_putstr_fd(hd_struct->the_line, hd_pipe_fd[1]);
			hd_struct = hd_struct->next;
		}
		close(hd_pipe_fd[1]);
		exit(0);
	}
	return (hd_pipe_fd[0]);
}

char *heredoc_dollar(/*char **env ,*/ char *line) // Il va falloir ajouter l'environnement
{
    int i;
    char *r_line;
    char *r_var;

    i = -1;
    r_line = NULL;
    r_var = NULL;
    while (line [++i] != '\0')
    {
        if (line[i] == '$')
        {
            if (line[++i] == '$')
                ;
            else if (line[i] == '?')
                r_line = ft_strjoin(r_line, ft_itoa(g_status));
            else if (line[--i] == '$')
            {
                while (line[++i] != '\'' && line[i] != '"' && ft_isspace(line[i]) != 0 && line[i] != '\0')
                    r_var = charjoinfree(r_var, line[i]);
//                r_var = cpy_env_var(/*env,*/ r_var);
                r_line = ft_strjoin(r_line, r_var);
                r_var = xfree(r_var);
            }
        }
        else
            r_line = charjoinfree(r_line, line[i]);
    }
    return (r_line);
}

void	print_hd(t_hdoc *hd)
{
	while (hd != NULL)
	{
		printf("%s\n", hd->the_line);
		hd = hd->next;
	}
}

void	heredoc_subparsing(t_data *data)
{
	char	*delimiter;
	// t_hdoc	*hd_data;
	t_tok	*tok_pointer_keeper;
	t_cmd	*cmd_pointer_keeper;

	tok_pointer_keeper = data->token;
	cmd_pointer_keeper = data->cmd_lst;
	while (data->token != NULL)
	{
		if (data->token->type == PIPE)
		{
			data->cmd_lst = data->cmd_lst->next;
			data->token = data->token->next;
		}
		if (data->token->type == HEREDOC)
		{
			delimiter = data->token->next->token;
			data->hd_struct = write_heredoc(delimiter);
			data->token = delmidnode_toklist(data->token);
			data->token = delmidnode_toklist(data->token);
			tok_pointer_keeper = get_first_tok(data->token);
		}
		data->token = data->token->next;
	}
	data->token = tok_pointer_keeper;
	data->cmd_lst = cmd_pointer_keeper;
}