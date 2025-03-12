/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:35:09 by emgul             #+#    #+#             */
/*   Updated: 2024/10/08 15:39:04 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int in_charset(char c, char *charset)
{
	int i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static int count_words(const char *s, char *charset)
{
	int i;
	int res;

	if (!s[0])
		return (0);
	i = 0;
	while (s[i])
	{
		if (in_charset(s[i], charset))
			i++;
		else
			break;
	}
	res = 0;
	while (s[i])
	{
		if (!in_charset(s[i], charset) && (i == 0 || in_charset(s[i - 1], charset)))
			res++;
		i++;
	}
	return (res);
}

static int count_letters(const char *s, char *charset)
{
	int i;

	i = 0;
	while (!in_charset(s[i], charset) && s[i] != '\0')
		i++;
	return (i);
}

static char *write_word(const char *s, char *charset)
{
	char *str;
	int i;

	str = (char *)malloc(count_letters(s, charset) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (!in_charset(s[i], charset) && s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char **ft_split_charset(char const *s, char *charset)
{
	char **arr;
	int i;
	int word;

	arr = (char **)malloc((count_words(s, charset) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	word = 0;
	while (s[i])
	{
		if (!in_charset(s[i], charset) && (i == 0 || in_charset(s[i - 1], charset)))
			arr[word++] = write_word(s + i, charset);
		i++;
	}
	arr[word] = 0;
	return (arr);
}
