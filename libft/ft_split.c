/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:08:24 by amousaid          #+#    #+#             */
/*   Updated: 2023/11/23 04:27:09 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countword(char *s1, char c)
{
	size_t	num;

	num = 0;
	while (*s1)
	{
		while (*s1 == c && *s1 != '\0')
			s1++;
		if (*s1 != c && *s1 != '\0')
			num++;
		while (*s1 != c && *s1 != '\0')
			s1++;
	}
	return (num);
}

static char	*ft_word_mal(char *s, char c)
{
	size_t	x;
	char	*ptr;

	x = 0;
	while (s[x] != c && s[x] != '\0')
		x++;
	ptr = malloc((x + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	x = 0;
	while (s[x] != c && s[x] != '\0')
	{
		ptr[x] = s[x];
		x++;
	}
	ptr[x] = '\0';
	return (ptr);
}

static char	**ft_free_all(char **ptr, size_t end)
{
	size_t	start;

	start = 0;
	while (start < end)
	{
		free(ptr[start]);
		ptr[start] = NULL;
		start++;
	}
	free(ptr);
	ptr = NULL;
	return (NULL);
}

static char	**mini_split(char const *s, char **ptr, char c, size_t x)
{
	while (*s)
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s != '\0')
		{
			ptr[x] = ft_word_mal((char *)s, c);
			if (ptr[x++] == NULL)
				return (ft_free_all(ptr, x));
		}
		while (*s != c && *s != '\0')
			s++;
		while (*s == c && *s != '\0')
			s++;
	}
	return (ptr[x] = NULL, ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	x;
	size_t	total;

	x = 0;
	if (s == NULL)
		return (NULL);
	total = ft_countword((char *)s, c);
	ptr = malloc(((total + 1) * sizeof(char *)));
	if (!ptr)
		return (NULL);
	return (mini_split(s, ptr, c, x));
}
// int main()
// {
// 	const char *str = "(-1-808-784-7895)";
// 	char **split_array = ft_split(str, '-');
// 	int i = 0;
// 	while(split_array[i])
// 		printf("%s",split_array[i++]);
// }