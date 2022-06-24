/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 02:21:21 by mmensing          #+#    #+#             */
/*   Updated: 2022/06/24 14:01:18 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	int	buff_len;
	int	line_len;
	int	rest_buff;

	buff_len = ft_strlen(buff);
	line_len = buff_len - ft_strlen(ft_strchr(buff, '\n') + 1);
	rest_buff = buff_len - line_len;
	ft_memmove(buff, &buff[line_len], rest_buff);
	ft_memset(&buff[rest_buff], '\0', line_len);
}

char	*end_of_file_no_nl(char *line_2, char *hold_2)
{
	line_2 = ft_strjoin(line_2, hold_2);
	ft_memset(hold_2, '\0', 1);
	return (line_2);
}

char	*get_next_line(int fd)
{
	static char	hold[1024][BUFFER_SIZE + 1];
	char		*line;
	int			val;

	if (fd < 0)
		return (NULL);
	line = calloc(1, sizeof(char));
	while (ft_strchr(hold[fd], '\n') == NULL)
	{
		if (hold[fd])
			line = ft_strjoin(line, hold[fd]);
		val = read(fd, hold[fd], BUFFER_SIZE);
		if (val <= 0 && *line == '\0')
		{
			free(line);
			return (NULL);
		}
		hold[fd][val] = '\0';
		if (val < BUFFER_SIZE && ft_strchr(hold[fd], '\n') == NULL)
			return (end_of_file_no_nl(line, hold[fd]));
	}
	line = ft_strjoin(line, hold[fd]);
	move_buff(hold[fd]);
	return (line);
}

// int main()
// {
//     int fd1 = open("test1.txt", O_RDONLY, 0);
//     int fd2 = open("test2.txt", O_RDONLY, 0);
// 	 printf("fd: %d\n", fd1);
// 	 printf("fd: %d\n", fd2);
// 	char *ptr;
// 	ptr = get_next_line(fd1);
// 	printf("Ptr %d: %s\n", fd1, ptr);
// 	free(ptr);
// 	ptr = get_next_line(fd2);
// 	printf("Ptr %d: %s\n", fd2, ptr);
// }