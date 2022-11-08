#include "../../include/minishell.h"

int	tok_len(char *str, int len)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (i < len)
	{
		if (is_set(str[i], METACHAR) || is_set(str[i], QUOTES)
			|| is_set(str[i], "$"))
		{
			if (i == 0 && ((is_set(str[i], QUOTES))))
				i = (1 + lenght_til_match(str, str[i]));
			if (i == 0 && (is_set(str[i], METACHAR)))
				i = (lenght_til_set(str, WHITESPACE));
			if (i == 0 && (is_set(str[i], "$")))
				i = (lenght_for_dollar(str));
			else if (i == 0)
				i = 1;
			break ;
		}
		else if (is_set(str[i], WHITESPACE))
			break ;
		i++;
	}
	return (i);
}

//ATENTION WHILE WORKING WITH $: CHECK RAW INPUT FOR SPACES BETWEEN $ AND WORDS.
//ALSO CHECK FOR REPETIONS (EX.: $??? or $$$$) WHILE MANAGING EXPANSION.
//SUB PARSING NEEDED AT THIS TIME.

int	lenght_for_dollar(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] == '$' || str[i] == '?' || is_set(str[i], WHITESPACE))
		{
			i++;
			break ;
		}
		else if (is_set(str[i], QUOTES))
		{
			i = (2 + lenght_til_match(&str[i], str[i]));
			break ;
		}
		else if (is_set(str[i], METACHAR))
			break ;
	i++;
	}
	return (i);
}

int	lenght_til_set(char *str, char *set)
{
	int	i;

	if (!str || !set)
		return (0);
	i = 1;
	while (str[i])
	{
		if (is_set(str[i], set) || !is_set(str[i], METACHAR))
			break ;
		i++;
	}
	return (i);
}

int	lenght_til_match(char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	i = 1;
	while (str[i])
	{
		if (is_set(str[i], &c))
			break ;
		i++;
	}
	return (i);
}
