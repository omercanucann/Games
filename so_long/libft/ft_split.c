/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:58:33 by oucan             #+#    #+#             */
/*   Updated: 2025/03/24 14:58:42 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(const char *s, const char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (*s)
	{
		if (*s == c)
			word = 0;
		else if (word == 0)
		{
			word = 1;
			i++;
		}
		s++;
	}
	return (i);
}

static char	*next_word(const char **s, char c)
{
	const char	*start;

	while (**s && **s == c)
	{
		(*s)++;
	}
	start = *s;
	while (**s && **s != c)
	{
		(*s)++;
	}
	return (ft_substr(start, 0, *s - start));
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		words;
	int		i;

	if (!s)
		return (0);
	words = ft_count_words(s, c);
	result = malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < words)
	{
		result[i] = next_word(&s, c);
		if (!result[i])
		{
			while (i > 0)
				free(result[--i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}
