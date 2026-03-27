/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:30:25 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/06/19 09:35:54 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static void	free_split(char **split, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static char	*extract_word(char const *s, char c, int *i)
{
	int		word_len;
	int		k;
	char	*word;

	while (s[*i] && s[*i] == c)
		(*i)++;
	word_len = 0;
	while (s[*i + word_len] && s[*i + word_len] != c)
		word_len++;
	word = malloc(word_len + 1);
	if (!word)
		return (NULL);
	k = 0;
	while (k < word_len)
	{
		word[k] = s[*i + k];
		k++;
	}
	word[k] = '\0';
	*i += word_len;
	return (word);
}

static char	**fill_result(char const *s, char c, char **result, int word_count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < word_count)
	{
		result[j] = extract_word(s, c, &i);
		if (!result[j])
		{
			free_split(result, j);
			return (NULL);
		}
		j++;
	}
	result[j] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	return (fill_result(s, c, result, word_count));
}
