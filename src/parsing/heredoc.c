#include "../../include/minishell.h"

t_hdoc	*ms_hd_dllst_new(char *str)
{
	t_hdoc	*new_node;

	new_node = malloc(sizeof(t_hdoc));
	if (new_node)
	{
		new_node->the_line = ft_strdup(str);
		new_node->next = NULL;
		new_node->previous = NULL;
	}
	return (new_node);
}

t_hdoc	*ms_hd_dllst_add_back(t_hdoc *p_lst, char *str)
{
	t_hdoc	*new_node;

	if (!p_lst)
		return (ms_hd_dllst_new(str));
	new_node = malloc(sizeof(t_hdoc));
	if (new_node)
	{
		while (p_lst->next != NULL)
			p_lst = p_lst->next;
		new_node->the_line =  ft_strdup(str);
		new_node->next = NULL;
		new_node->previous = p_lst;
		p_lst->next = new_node;
		while (p_lst->previous != NULL)
			p_lst = p_lst->previous;
		return (p_lst);
	}
	return (NULL);
}


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

	line = NULL;
	hd_struct = NULL;
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, delimiter) == 0)
			break;
		line = ft_strjoin(line, "\n");
		hd_struct = ms_hd_dllst_add_back(hd_struct, line);
		if (line)
			line = xfree(line);
		// Sans doute la meilleur endroit pour la gestion des $sign (expention)
	}
	if (line)
		line = xfree(line);
	printf("break\n");
	return (hd_struct);
}

/* MiniMan of the functions in this file.
 * PROTOTYPE:
 *     t_hdoc	*heredoc(char *delimiter);
 * The function simulate a here-document in creating a linked list for store
 * the input line(node) by line(node). FOr info, a heredoc redirect a bunch
 * of lines to the stdin.
 */
//trouver le delimiter du heredoc
//prompt a l utilisateur pour l ecriture du heredoc
//supprimer le token et le delimiter du heredoc
//retoruner la structure du heredoc
// t_hdoc	*heredoc_parsing(char *line)
// {
// 	int		i;
// 	char	*delimiter;
// 	int		del_len;
// 	t_hdoc	*hd_data;

// 	i = 0;
// 	while(line[i] != '\0' && line[i + 1] != '\0')
// 	{
// 		if (line[i] == '<' && line[i + 1] != '<')
// 		{
// 			while (line[++i] == ' ')
// 				i++;
// 			del_len = first_word_len(&line[i]);
// 			delimiter = ft_substr(line, i, del_len);
// 			hd_data = write_heredoc(delimiter);
// 			return (hd_data);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

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
		while (hd_struct != NULL)
		{
			close(hd_pipe_fd[0]);
			ft_putstr_fd(hd_struct->the_line, hd_pipe_fd[1]);
			hd_struct = hd_struct->next;
		}
		close(hd_pipe_fd[1]);
		exit(0);
	}
	else
		close(hd_pipe_fd[1]);
	return (hd_pipe_fd[0]);
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