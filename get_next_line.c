/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:46:54 by naankour          #+#    #+#             */
/*   Updated: 2024/12/02 15:21:05 by naankour         ###   ########.fr       */
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
		return (NULL);
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

char	*ft_strdup(char *src)
{
	char	*dest;
	int		i;

	i = 0;
	if (!src || src[0] == '\0')
	{
		return(NULL);
	}
	if (ft_strchr(src, '\n') == 1)
	dest = (char *)malloc(sizeof (char) * (ft_strlen(src) + 2 ));
	if (ft_strchr(src, '\n') == 0)
	dest = (char *)malloc(sizeof (char) * (ft_strlen(src) + 1 ));
	if (!dest)
		return (NULL);
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

char	*ft_update_buffer(char *buffer)
{
	int		i;
	int		index;
	char	*updated_buffer;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\0')
	{
		free (buffer);
		return (NULL);
	}
	i++;
	updated_buffer = malloc(sizeof(char) * ((ft_strlen(buffer)- i+ 1)));
	if (!updated_buffer)
	{
		free (buffer);
		return (NULL);
	}
	index = 0;
	while (buffer[i] != '\0')
	{
		updated_buffer[index++] = buffer[i++];
	}
	updated_buffer[index] = '\0';
	free(buffer);
	return (updated_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char	*temp;
	char	*line;
	int	r;

	if (fd < 0 || BUFFER_SIZE <= 0)
			return (NULL);
	temp = malloc(sizeof (char) * (BUFFER_SIZE + 1));
	if (!temp)
	{
		free(temp);
		free(buffer);
		return (NULL);
	}
	while(!(ft_strchr(buffer, '\n')))
	{
		r = read(fd, temp, BUFFER_SIZE);
		if (r <= 0)
		{
			if (r == 0)
				break;
			free (buffer);
			free(temp);
			buffer = NULL;
			return NULL;
		}
		temp[r] = '\0';
		buffer = ft_strjoin(buffer, temp);
	}
	free (temp);
	if (!buffer || buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return NULL;
	}
	line = ft_strdup(buffer);
	buffer = ft_update_buffer(buffer);
	return (line);
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
// 	{
// 		printf("tu sais meme pas ouvrir un fichier la honte");
// 		return (0);
// 	}
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
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
