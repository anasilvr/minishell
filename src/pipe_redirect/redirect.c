/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:34:45 by tchalifo          #+#    #+#             */
/*   Updated: 2022/11/08 17:18:55 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* RETURN VALUE of functions
 * - redirect_to_file()
 *   Return the file descriptor of the opened file. Return -1 and set errno
 *   if the file can't be open.
 *
 * - redirect_from_file()
 *
 * */


/* Case cmd > file --> Redirect the standard output (stdout) of cmd to a file
 * and replace all the content for the new one.
 * Case cmd >> file --> Append the standard output (stdout) of cmd to a file.
 * So i need to
 * - Open the file, if is not present create im or if i dont have permission
 *   on it return the error code -1.
*/
int	file_opening(char *filepath, int flag)
{
	int	file_fd;

	file_fd = open(filepath, O_CREAT);
	if (file_fd == -1)
		return (-1);
	return (file_fd);
}
/* Puisque je trouve tout les infos sur la string retourné par
 * readline dans la struct token, j'ai utilisé les champs de la
 * list chainée Token.
 * La variable type m'indique si je rencontre un chevrons < en autre qui est
 * l'enum de valeur 4.
 * Donc, ici si je rencontre un chevrons, le nom du fichier devrait
 * le précéder.
 */
void	input_setup(t_data *data)
{
	if (data->token->type == REDIR_IN)
	{
		while (data->token->next != '\0')
		{
			if (ft_strcmp(data->token->type, '<') == 0)
				break;
			data->token = data->token->next;
		}
		file_opening(data->token->prev->token, "");
	}
}

/* Puisque je trouve tout les infos sur la string retourné par
 * readline dans la struct token, j'ai utilisé les champs de la
 * list chainée Token.
 * La variable type m'indique si je rencontre un chevrons > en autre qui est
 * l'enum de valeur 5.
 * Donc, ici si je rencontre un chevrons, le nom du fichier devrait le suivre.
 */
void	output_setup(t_data *data)
{
	if (data->token->type == REDIR_OUT)
	{
		while (data->token->next != '\0')
		{
			if (ft_strcmp(data->token->type, '>') == 0)
				break;
			data->token = data->token->next;
		}
		file_opening(data->token->next->token, "");
	if (data->token->type == APPEND)
	{
		while (data->token->next != '\0')
		{
			if (ft_strcmp(data->token->type, '>>') == 0)
				break;
			data->token = data->token->next;
		}
		file_opening(data->token->next->token, "APPEND");
	}
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
void	heredoc()
{
	char *content;
	int	readlen;

	readlen = 1;
	while (readlen > 0)
		content = read();

}

/* Case cmd < file --> Redirect the contents of the file to the standard
 * input (stdin) of cmd.
 */
void	redirect_from_file(char *filepath)
{

}
