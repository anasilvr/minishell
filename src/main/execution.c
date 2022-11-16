#include "../../include/minishell.h"
/* Les différents possibilitées de traitement des redirections par Bash
 * bonjour > cat == ERROR zsh: command not found: bonjour && open a créé le fichier cat s'il n'existait pas
 * bonjour >> cat == ERROR zsh: command not found: bonjour && open a créé le fichier cat s'il n'existait pas
 * bonjour < cat == ERROR zsh: no such file or directory: cat
 * echo bob > cat == SUCCESS fichier cat créé avec le mot bob à l'intérieur
 * cat < file (file 1 exist)== SUCCESS Content of file are put in stdin of cat and is stdout go to terminal
 * cat < file2 (file2 not exist) == ERROR zsh: no such file or directory: file2
 *
 */

/* Un exemple de chaine d'execution possible
 * file1 > echo | cat > file2 > file3 > cat | cat | cat >> file4
 *
 *
 *
 * /

/* 1. file1
 * 1.1 setup input to stdin (0)


 */

/* Conclusions :
 * 1. Vérifier si le node est un type autre qu'un exec ou fichier. Si c'est autre execve me retournera un (voir Anna pour parsing)


*/

void	exec_chain(void)
{
	while (cmd_chain != NULL)
	{
		if (cmd_chain_name == '|')
		{

		}
		else if(cmd_chain_name == '>')
		{}
		else if(cmd_chain_name == '<')
		{}
		else if(cmd_chain_name == '>>')
		{}
		else if(cmd_chain_name == '<<')
		{}
		else if(cmd_chain_name == cmd(cmd_chain_name))
		cmd_chain = cmd_chain->next
	}
}
