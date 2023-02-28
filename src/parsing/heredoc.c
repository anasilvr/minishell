#include "../../include/minishell.h"

/* MiniMan of the functions in this file.
 * PROTOTYPE:
 *     t_hdoc	*heredoc(char *delimiter);
 * The function simulate a here-document in creating a linked list for store
 * the input line(node) by line(node). FOr info, a heredoc redirect a bunch
 * of lines to the stdin.
*/

/* Case cmd << EOL --> Redirect a bunch of lines to the stdin. This is called
 * a here-document.
 * exemple:
 * cmd << EOL
 * line1
 * line2
* EOL
*/
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

//trouver le heredoc
//supprimer le heredoc
t_hdoc	*heredoc_parsing(char *line)
{
	int		i;
	char	*delimiter;
	int		del_len;
	t_hdoc	*hd_data;

	i = 0;
	while(line[i] != '\0' && line[i + 1] != '\0')
	{
		if (line[i] == '<' && line[i + 1] != '<')
		{
			while (line[++i] == ' ')
				i++;
			del_len = first_word_len(&line[i]);
			delimiter = ft_substr(line, i, del_len);
			hd_data = write_heredoc(delimiter);
			return (hd_data);
		}
		i++;
	}
	return (NULL);
}

//Probleme avec cela, si le heredoc est en plein milieux ca va enlever la suite... cat <<EOF >> outfile  ..>>outfile ne sera plus..
char	*heredoc_trim(char *line)
{
	int		start;
	int		len;
	int		i;

	i = 0;
	start = 0;
	len = 0;
	while (line[i] != '\0')
	{
		while (line[i] != '\0')
		{
			if (line[i] == '<' && line[i + 1] == '<')
			{
				i += 2;
				while (line[i] == ' ')
					i++;
				break;
			}
			if (start == 0 && i != 0 && len < 1)
				start = i;
			len++;
			i++;
		}
		while (line[i] != '\0' && line[i++] != ' ')
			len++;
	}
	return (ft_strtrim(ft_substr(line, start, len), " "));
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

// bool	is_heredoc(t_cmd *cmd_lst)
// {
// 	while (cmd_lst->next != NULL)
// 	{
// 		if (cmd_lst->heredoc == true)
// 			return(1);
// 		cmd_lst = cmd_lst->next;
// 	}
// 	return (0);
// }