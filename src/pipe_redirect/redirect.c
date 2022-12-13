/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:34:45 by tchalifo          #+#    #+#             */
/*   Updated: 2022/12/12 13:22:11 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* MiniMan of the functions in this file.
 * PROTOTYPE:
 *    void	redirect_manager(t_data *prog_data);
 * if an io_flag of redirection is encountered a file descriptor
 * (filefd pointer) is assigned to a file and it can be open in read only or
 * read/write depending on the flag. The second fd from the tab pointer is
 * closed with value of -2. if no flag are corresponding to a redirection,
 * -2 is assigned at the two filefd tab pointers.
 * PROTOTYPE:
 *     static int	open_to_read(char *filepath, int *additional_flag);
 * Simply attribute a file descriptor to open a file in read only mode and
 * return the fd value. If an error occuring, -1 is return and errno is print.
 * PROTOTYPE:
 *     static int open_to_readwrite(char *filepath, int *additional_flag);
 * Simply attribute a file descriptor to open a file in read/write mode and
 * return the fd value. If an error occuring, -1 is return and errno is print.
 * PROTOTYPE:
 *     t_hdoc	*heredoc(char *delimiter);
 * The function simulate a here-document in creating a linked list for store
 * the input line(node) by line(node). FOr info, a heredoc redirect a bunch
 * of lines to the stdin.
*/

/* MEMORY ZONE OF THOMAS FISH
 * Case cmd > file --> Redirect the standard output (stdout) of cmd to a file
 * and replace all the content for the new one.
 * Case cmd >> file --> Append the standard output (stdout) of cmd to a file.
 */

static int	open_to_read(char *filepath, int *additional_flag)
{
	int	file_fd;
	(void) additional_flag;

	if (access(filepath, R_OK) == -1) //&& errno != ENOENT)
	{
		perror(NULL);
		return (-1);
	}
	else
	{
		file_fd = open(filepath, O_RDONLY);
		if (file_fd == -1)
		{
			perror(NULL);
			return (-1);
		}
	}
	return (file_fd);
}

static int	open_to_readwrite(char *filepath, int *additional_flag)
{
	int	file_fd;
	/* In case where the file exist but no have the right on it */
	if (access(filepath, R_OK | W_OK) == -1 && errno == EACCES)
	{
		perror(NULL);
		return (-1);
	}
	else
		file_fd = open(filepath, O_WRONLY | additional_flag[0] | O_CREAT, \
				S_IWUSR | S_IWGRP | S_IWOTH | S_IRUSR | S_IRGRP | S_IROTH);
		if (file_fd == -1)
		{
			perror(NULL);
			return (-1);
		}
	return (file_fd);
}

void	redirect_manager(t_data *prog_data)
{
	int	open_additionals_flags[1];

	// if (prog_data->cmd_lst->io_flag == 3) //if is a heredoc
	// 	prog_data->hd_struct = write_heredoc(char *delimiter); //Need to know where is stored the delimiter

	if (prog_data->cmd_lst->io_flag == 4) //if is an input redirect <
	{
		prog_data->cmd_lst->filefd[0] = open_to_read \
		(prog_data->cmd_lst->next->args[0], open_additionals_flags);
		prog_data->cmd_lst->filefd[1] = -2; //-2 = is close
	}
	else if (prog_data->cmd_lst->io_flag == 5) //if is an output redirect > (Open file and put the fd into struct in int *cmdio_fd)
	{
		open_additionals_flags[0] = O_TRUNC;
		prog_data->cmd_lst->filefd[1] = open_to_readwrite \
		(prog_data->cmd_lst->next->args[0], open_additionals_flags); // voir a supprimer le contenue completemnet a chaque fois
		prog_data->cmd_lst->filefd[0] = -2; //-2 = is close
	}
	else if (prog_data->cmd_lst->io_flag == 6) //if is an output redirect in append mode >> (Open file and put the fd into struct in int *cmdio_fd)
	{
		open_additionals_flags[0] = O_APPEND;
		prog_data->cmd_lst->filefd[1] = open_to_readwrite \
		(prog_data->cmd_lst->next->args[0], open_additionals_flags);
		prog_data->cmd_lst->filefd[0] = -2; //-2 = is close
	}
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
	char	*content;
	char	*line;
	t_hdoc	*hd_struct;

	content = (char *) NULL;
	line = (char *) NULL;
	while (ft_strcmp(delimiter, line))
	{
		if (line)
		{
			free(line);
			line = (char *) NULL;
		}
		line = readline("> ");
		line = ft_strjoin_free(line, "");
		hd_struct = ft_dllst_add_back(hd_struct, line);
	}
	return (hd_struct);
}

// int	heredoc_to_fd(t_hdoc *hd_struct)
// {
// 	//need to continue with a way to pitch to the stdin the line stored in char *var
// }

// tchalifo@c2r1p11 minishell % echo salut >> file.txt > toto.sh

// tchalifo@c2r1p11 minishell % cat file.txt
// bob
// salut
// salut

// tchalifo@c2r1p11 minishell % cat toto.sh
// salut

// tchalifo@c2r1p11 minishell % echo salut >> file.txt >> toto.sh

// tchalifo@c2r1p11 minishell % cat toto.sh
// salut
// salut

// tchalifo@c2r1p11 minishell % echo salut >> file.txt > toto.sh

// tchalifo@c2r1p11 minishell % cat toto.sh
// salut

// sed 's/bib/lol/' file.txt > file2.txt