/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:58:06 by tpicoule          #+#    #+#             */
/*   Updated: 2023/02/16 12:16:34 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_counti(char *s, char c)
{
	size_t	i;
	size_t	k;

	k = 0;
	i = 0;
	if (s[i] == c)
		i++;
	if (s[0] != c || s[i + 1] == '\0')
		k++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			k++;
		i++;
	}
	if (s[0] == c && k > 0)
		k++;
	return (k);
}

char	**ft_countj(char **tabtab, char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	x;

	i = 0;
	j = 0;
	x = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		j = i;
		if (s[i])
		{
			while (s[i] != c && s[i])
				i++;
			tabtab [x] = ft_substr(s, j, i);
			x++;
		}
	}
	tabtab [x] = NULL;
	return (tabtab);
}

char	**funct_split(char *s, char c)
{
	char	**tabtab;

	if (!s)
	{
		tabtab = malloc(sizeof(char) * 1);
		if (!tabtab)
			return (NULL);
		tabtab[0] = 0;
		return (tabtab);
	}
	tabtab = malloc(sizeof(char *) * (ft_counti(s, c) + 1));
	if (!tabtab)
		return (NULL);
	tabtab = ft_countj(tabtab, s, c);
	return (tabtab);
}

char	*ft_strjoin(char *s1, char *s2)

{
	char	*result;
	int		i;
	int		n;

	if (!s1 || !s2)
		return (NULL);
	result = malloc((sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!result)
		return (NULL);
	i = 0;
	n = 0;
	if (!s2)
		return (NULL);
	while (s1[i])
		result[n++] = s1[i++];
	result[n++] = '/';
	i = 0;
	while (s2[i])
		result[n++] = s2[i++];
	result[n] = '\0';
	return (result);
}

char	*ft_substr(char *s, int start, int end)

{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = start;
	ret = malloc((end - start + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (i < end - start)
		ret[i++] = s[j++];
	ret[i] = '\0';
	return (ret);
}
