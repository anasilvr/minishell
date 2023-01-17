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

// int	*init_itab(int init_value, int init_size)
// {
// 	int	*itab;

// 	itab = malloc(sizeof(int) * init_size);
// 	itab[0] = init_value;
// 	return (itab);
// }
