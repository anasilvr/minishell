/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:34:45 by tchalifo          #+#    #+#             */
/*   Updated: 2022/11/07 15:24:56 by tchalifo         ###   ########.fr       */
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
int	redirect_to_file(char *filepath)
{
	int	file_fd;

	file_fd = open(filepath, O_CREAT);
	if (file_fd == -1)
		return (-1);
	return (file_fd);
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
