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

// Ma conclusion sur la chaine d'execution.

/* Premier token de la chaine d'execution :
 * 1.  Si le token présent est une commande, elle sera executé.
 * ---
 * 2.  Si le token présent est une redirection d'input ( > ), il créer le
 * fichier avec pour nom le token suivant sans plus. (Voir doc sur
 * "Les redirections").
 * ---
 * 3.  Si le token présent est quelque chose d'autre qu'une commande ou une
 * redirection d'input, il y aura un retour d'erreur (command not found).
 */
/* Deuxieme token et ceux en millieu de chaine d'execution :
 * 1 Si le token présent est une commande :
 *  1.1 Et que le token précédent est :
 *   1.1.1 Une commande, le token précédent sera executé avec pour arguments
 *         le ou les token(s) qui suive(nt). Donc tout les tokens suivant la commande
 *         executée sont traité comme argument tant qu'un autre type de token ne sera
 *         pas rencontré (redirection ou pipe).
 *         des commande(s) tant qu'une redirection ou
 *     un pipe n'aura pas étét rencontré.
 * 1.2 Si le token précédent est :
 * 1.2.1 Si le précédent token est une redirection
 *
 *1.2 et que le token suivant
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