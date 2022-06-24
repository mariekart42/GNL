/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 22:13:30 by mmensing          #+#    #+#             */
/*   Updated: 2022/06/24 15:04:20 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	rev_func(size_t i, size_t n, char *st1, char *st2)
{
	while (i < n)
	{
		st1[i] = st2[i];
		i++;
	}
}

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	size_t	i;
	int		rev_i;
	char	*st1;
	char	*st2;

	if (!str1 && !str2)
		return (NULL);
	i = 0;
	rev_i = n - 1;
	st1 = (char *)str1;
	st2 = (char *)str2;
	if (str1 < str2)
	{
		rev_func(i, n, st1, st2);
		return (str1);
	}
	while (i++ < n)
	{
		st1[rev_i] = st2[rev_i];
		rev_i--;
	}
	return (str1);
}

void	move_buff(char *buff)
{
	int	buff_length;
	int	line_lenght;
	int	rest_buff;

	buff_length = ft_strlen(buff);
	line_lenght = buff_length - ft_strlen(ft_strchr(buff, '\n') + 1);
	rest_buff = buff_length - line_lenght;
	ft_memmove(buff, &buff[line_lenght], rest_buff);
	ft_memset(&buff[rest_buff], '\0', line_lenght);
}

char	*end_of_file_no_nl(char *line_2, char *hold_2)
{
	line_2 = ft_strjoin(line_2, hold_2);
	ft_memset(hold_2, '\0', 1);
	return (line_2);
}

char	*get_next_line(int fd)
{
	static char	hold[BUFFER_SIZE +1];
	char		*line;
	int			val;

	if (fd < 0)
		return (NULL);
	line = calloc(1, sizeof(char));
	while (ft_strchr(hold, '\n') == NULL)
	{
		if (*hold)
			line = ft_strjoin(line, hold);
		val = read(fd, hold, BUFFER_SIZE);
		if (val <= 0 && !*line)
		{
			free(line);
			return (NULL);
		}
		hold[val] = '\0';
		if (val < BUFFER_SIZE && ft_strchr(hold, '\n') == NULL)
			return (end_of_file_no_nl(line, hold));
	}
	line = ft_strjoin(line, hold);
	move_buff(hold);
	return (line);
}

// int main()
// {
//      int fd = open("binary.bin", O_RDONLY, 0);
// 	 printf("fd: %d\n", fd);
// 	int i = 1;
// 	char *ptr;
// 	while (i < 8)
// 	{
// 		ptr = get_next_line(fd);
// 		printf("Ptr %d: %s\n", i, ptr);
// 		free(ptr);
// 		i++;
// 	}
// }