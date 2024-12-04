/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:22:24 by naankour          #+#    #+#             */
/*   Updated: 2024/12/04 11:45:47 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read(int fd, char *buffer, char *temp)
{
	int	r_nbytes;

	while (!(ft_strchr(buffer, '\n')))
	{
		r_nbytes = read(fd, temp, BUFFER_SIZE);
		if (r_nbytes <= 0)
		{
			if (r_nbytes == 0)
				break ;
			free (buffer);
			buffer = NULL;
			return (NULL);
		}
		temp[r_nbytes] = '\0';
		buffer = ft_strjoin(buffer, temp);
		if (!buffer)
		{
			free (temp);
			return (NULL);
		}
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[4096];
	char		*temp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = malloc(sizeof (char) * (BUFFER_SIZE + 1));
	if (!temp)
	{
		free(temp);
		free(buffer[fd]);
		return (NULL);
	}
	buffer[fd] = ft_read(fd, buffer[fd], temp);
	free (temp);
	if (!buffer[fd] || buffer[fd][0] == '\0')
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	line = ft_strdup(buffer[fd]);
	buffer[fd] = ft_update_buffer(buffer[fd]);
	return (line);
}
// int main(void)
// {
// 	int		fd1, fd2, fd3;
// 	char	*line;

// 	fd1 = open("testgnl1.txt", O_RDONLY);
// 	if (fd1 == -1)
// 	{
// 		printf("Impossible d'ouvrir le fichier testgnl1.txt\n");
// 		return (1);
// 	}

// 	fd2 = open("testgnl2.txt", O_RDONLY);
// 	if (fd2 == -1)
// 	{
// 		printf("Impossible d'ouvrir le fichier testgnl2.txt\n");
// 		close(fd1);
// 		return (1);
// 	}

// 	fd3 = open("testgnl3.txt", O_RDONLY);
// 	if (fd3 == -1)
// 	{
// 		printf("Impossible d'ouvrir le fichier testgnl3.txt\n");
// 		close(fd1);
// 		close(fd2);
// 		return (1);
// 		}

// 	while ((line = get_next_line(fd1)))
// 	{
// 		printf("Fichier 1: %s", line);
// 		free(line);
// 	}
// 	close(fd1);

// 	while ((line = get_next_line(fd2)))
// 	{
// 		printf("Fichier 2: %s", line);
// 		free(line);
// 	}
// 	close(fd2);

// 	while ((line = get_next_line(fd3)))
// 	{
// 		printf("Fichier 3: %s", line);
// 		free(line);
// 	}
// 	close(fd3);

// 	return (0);
// }