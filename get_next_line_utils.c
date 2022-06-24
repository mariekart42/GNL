/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 22:55:32 by mmensing          #+#    #+#             */
/*   Updated: 2022/06/24 14:03:53 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

/**
 * @brief returns lengh of str
 * 
 * @param str 
 * @return size_t lengh of str
 */
size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

/**
 * @brief function connects to given strings and allocates
 * memory for them with malloc
 * 
 * @param s1 fist string
 * @param s2 second string
 * @return char pointer to allocated memory space
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		k;

	if (!s1 || !s2)
		return ((char *)s1);
	ptr = (char *) calloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1, 1);
	if (!ptr)
		return (NULL);
	k = 0;
	i = 0;
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[k] != '\n' && s2[k] != '\0')
	{
		ptr[i] = s2[k];
		i++;
		k++;
	}
	if (s2[k] && s2[k] == '\n')
		ptr[i] = '\n';
	return (ptr);
}

/**
 * @brief   function searches for the FIRST occurrence in str for character c
            if str doesnt end with NUL program might crash 
 * @param str string where c should get found
 * @param c the character we are searching for 
 * @return char*    returns pointer to string at the position where 'c' was found
                    returns NULL if not found
 */
char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	if (str[0] == (char) c)
		return ((char *) str);
	while (str[i] != '\0')
	{
		if ((c == '\0') && (str[i + 1] == '\0'))
			return ((char *) str + i + 1);
		if (str[i] == (char)c)
		{
			return ((char *) str + i);
		}
		i++;
	}
	return ((char *) '\0');
}

void	*ft_memset(void *str, int c, size_t n)
{
	char	*ptr;
	size_t	i;

	ptr = (char *) str;
	i = 0;
	while (i < n)
	{
		ptr[i] = c;
		i++;
	}
	str = (void *) ptr;
	return (str);
}
