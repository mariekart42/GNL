/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 22:13:30 by mmensing          #+#    #+#             */
/*   Updated: 2022/07/18 20:49:18 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;
	size_t			i;

	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	i = 0;
	if (d > s)
	{
		while (n)
		{
			n = n - 1;
			d[n] = s[n];
		}
	}
	else
	{
		while (n)
		{
			d[i] = s[i];
			i++;
			n--;
		}
	}
	return (dest);
}

void	buff_after_line(char *buff)
{
	int			rest_buff;

	rest_buff = ft_strlen(buff) - ft_strlen(ft_strchr(buff, '\n') + 1);
	ft_memmove(buff, &buff[rest_buff], ft_strlen(ft_strchr(buff, '\n') + 1));
	buff[ft_strlen(buff) - rest_buff] = '\0';
}

char	*create_last(char *buff, char *line)
{
	line = ft_strjoin(line, buff);
	buff[0] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*line;
	int			count;

	if (fd < 0)
		return (NULL);
	line = (char *)malloc(sizeof(char));
	line[0] = '\0';
	while (!ft_strchr(buff, '\n'))
	{
		if (*buff)
			line = ft_strjoin(line, buff);
		count = read(fd, buff, BUFFER_SIZE);
		if (count <= 0 && (!*line))
		{
			free(line);
			return (NULL);
		}
		buff[count] = '\0';
		if (!ft_strchr(buff, '\n') && count < BUFFER_SIZE)
			return (create_last(buff, line));
	}
	line = ft_strjoin(line, buff);
	buff_after_line(buff);
	return (line);
}
