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
	char	*content;
	char	*line;
	t_hdoc	*hd_struct;

	content = (char *) NULL;
	line = (char *) NULL;
	while (ft_strcmp(delimiter, line))
	{
		if (line)
		{
			xfree(line);
			//line = (char *) NULL;
		}
		line = readline("> ");
		line = ft_strjoin_free(line, "");
		hd_struct = ft_dllst_add_back(hd_struct, line);
	}
	return (hd_struct);
}

int	heredoc_to_fd(t_hdoc *hd_struct)
{
	while (hd_struct->next != NULL)
	{
		ft_putstr_fd(hd_struct->the_line, 1);
		hd_struct = hd_struct->next;
	}
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