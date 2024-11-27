/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:46:54 by naankour          #+#    #+#             */
/*   Updated: 2024/11/27 16:22:14 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return(0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new = malloc(s1_len + s2_len + 1);
	if (!new)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	if (s1)
	{
		while (s1[i] != '\0')
		{
			new[i] = s1[i];
			i++;
		}
	}
	j = 0;
	if (s2)
	{
		while (s2[j] != '\0')
		{
			new[i + j] = s2[j];
			j++;
		}
	}
	new[s1_len + s2_len] = '\0';
	if (s1)
		free(s1);
	return (new);
}

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return(0);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*strduperd( char *src)
{
	char	*dest;
	int		i;

	i = 0;
	if (!src || src[0] == '\0')
	{
		return(NULL);
	}
	dest = (char *)malloc(sizeof (char) * (ft_strlen(src) +2 ));
	if (!dest)
	{
		return (NULL);
	}
	while (src[i] != '\0' && src[i] != '\n')
	{
		dest[i] = src[i];
		i++;
	}
	if (src[i] == '\n')
	{
		dest[i] = '\n';
		i++;
	}
	dest[i] = '\0';
	return (dest);
}


char	*ft_update_buffer(char const *lean, char *buffer)
{
	int		i;
	int		index;
	char	*updated_buffer;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	index = ft_strlen(lean);
	if (buffer[i] == '\0')
		return (NULL);
	i++;
	updated_buffer = malloc(sizeof(char) * (i- index + 1));
	if (!updated_buffer)
		return (NULL);
	i = 0;
	while (buffer[index] != '\0')
	{
		updated_buffer[i++] = buffer[index++];
	}
	updated_buffer[i] = '\0';
	free(buffer);
	return (updated_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char	*temp;
	char	*lean;
	int	r;

	temp = malloc(sizeof (char) * (BUFFER_SIZE + 1));
	if (!temp)
	{
		temp = NULL;
		buffer = NULL;
		return (NULL);
	}

	while((!(ft_strchr(buffer, '\n'))))
	{
		r = read(fd, temp, BUFFER_SIZE);
		if (r == 0)
			break ;
		temp[r] = '\0';
		buffer = ft_strjoin(buffer, temp);
		if (!buffer)
			return NULL;
	}
	if (!buffer || buffer[0] == '\0')
	{
		buffer = NULL;
		return (NULL);
	}
	lean = strduperd(buffer);
	buffer = ft_update_buffer(lean, buffer);
	if (r == 0)
	{
		free(buffer);
		return(NULL);
	}
	free(temp);
	return (lean);
}


// int	main (void)
// {

// 	//char	buf[BUFFER_SIZE + 1];
// 	int	fd;
// 	//int	nb_read;
// 	//int	count;
// 	char	*line;

// 	fd = open("testgnl.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (1);
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 	}
// 	// nb_read = -1;
// 	// count = 0;
// 	// while (nb_read != 0)
// 	// {
// 	// 	nb_read = read(fd, buf, BUFFER_SIZE);
// 	// 	if (nb_read == -1)
// 	// 	{
// 	// 		printf("Erreur de lecture !\n");
// 	// 		return (1);
// 	// 	}
// 	// 	buf[nb_read] = '\0';
// 	// 	printf("%s", buf);
// 	// 	count ++;
// 	// }
// 	close(fd);
// 	return (0);
// }
