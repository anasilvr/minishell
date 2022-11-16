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
				i = (1 + length_til_match(str, str[i]));
			if (i == 0 && (is_set(str[i], METACHAR)))
				i = (length_til_set(str, WHITESPACE));
			if (i == 0 && (is_set(str[i], "$")))
				i = (length_for_dollar(str));
			else if (i == 0)
				i = 1;
			return (i);
		}
		else if (is_set(str[i], WHITESPACE))
			break ;
		i++;
	}
	return (i);
}

//ATENTION WHILE WORKING WITH $: CHECK RAW INPUT FOR SPACES BETWEEN $ AND WORDS. (Ana)
//ALSO CHECK FOR REPETIONS (EX.: $??? or $$$$) WHILE MANAGING EXPANSION. (Probably Thomas)
//SUB PARSING NEEDED AT THIS TIME.

int	length_for_dollar(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 1;

	if (str[i] == '$' || str[i] == '?' || is_set(str[i], WHITESPACE))
	{
		i++;
		return (i);
	}
	else if (is_set(str[i], QUOTES))
	{
		i = (2 + length_til_match(&str[i], str[i]));
		return (i);
	}
	else
	{
		while (str[i] && (!is_set(str[i],WHITESPACE) && \
			!is_set(str[i], METACHAR)))
			i++;
	}
	return (i);
}

int	length_til_set(char *str, char *set)
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

int	length_til_match(char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	i = 1;
	while (str[i])
	{
		if ((str[i]) == c)
			break ;
		i++;
	}
	return (i);
}
