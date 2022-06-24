/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 22:13:30 by mmensing          #+#    #+#             */
/*   Updated: 2022/06/24 02:21:09 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


//Return one line that's allocated
//Keep track of the readings in the static buffer
//so on each iteration
//You go check if there new line in the buffer
//if there isn't then you merge the remainder with the line
//and you read again till you reach the end of the file or you found a new line so that means you have line that you can return
//if there isn't join the buffer with line and return the line
//Update the buffer before returning so delete line from it 


//file "S"
//BUffersize = 2
//S
//return NULL;
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

void move_buff(char *buff)
{
	int buff_length = ft_strlen(buff);
	int line_lenght = buff_length - ft_strlen(ft_strchr(buff, '\n') + 1);
	int rest_buff = buff_length - line_lenght;
	ft_memmove(buff, &buff[line_lenght], rest_buff);
	ft_memset(&buff[rest_buff], '\0', line_lenght);
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
		{
			line = ft_strjoin(line, hold);
			ft_memset(hold, '\0', 1);
			return (line);
		}
	}
	line = ft_strjoin(line, hold);
	move_buff(hold);
	return line;
}

// before n 

//Static 
//Greeter()
//char arr[50] = "Siemanko"
//Greater()
//char arr[50]
//This allocates new memory each time your run the function and also arr[50] dissapers on the function end

//Static
//static char[50] = "Siemanko";
//Greater()
//Greater()
//static char[50] --- 

//Static char *str = mallo("Siemanko");
//free()

//Pointer is just 

//Array is basically the space in memory allocated next to each other
//[0][1][2][0][3]
//char
//1 byte
//60
//[0][1][2][3]

//char *ptr;
//4 bytes
//This pointer points to the allocated memory
//ptr = malloc(sizeof(char), 60); 
//


// int main()
// {
//      int fd = open("test2.txt", O_RDONLY, 0);
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