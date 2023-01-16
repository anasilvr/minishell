#include "../../include/minishell.h"

int	first_word_len(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0' && str[len] != ' ') // Voir a ajouter si besoin d<autre whitespaces
	{
		len++;
	}
	return (len);
}