/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:46:54 by naankour          #+#    #+#             */
/*   Updated: 2024/12/03 15:16:25 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *buffer, char *temp)
{
	int	r;

	while (!(ft_strchr(buffer, '\n')))
	{
		r = read(fd, temp, BUFFER_SIZE);
		if (r <= 0)
		{
			if (r == 0)
				break ;
			free (buffer);
			buffer = NULL;
			return (NULL);
		}
		temp[r] = '\0';
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
	static char	*buffer = NULL;
	char		*temp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = malloc(sizeof (char) * (BUFFER_SIZE + 1));
	if (!temp)
	{
		free(temp);
		free(buffer);
		return (NULL);
	}
	buffer = ft_read(fd, buffer, temp);
	free (temp);
	if (!buffer || buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = ft_strdup(buffer);
	buffer = ft_update_buffer(buffer);
	return (line);
}

int	main (void)
{

	//char	buf[BUFFER_SIZE + 1];
	int	fd;
	//int	nb_read;
	//int	count;
	char	*line;

	fd = open("testgnl.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("tu sais meme pas ouvrir un fichier la honte");
		return (0);
	}
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	// nb_read = -1;
	// count = 0;
	// while (nb_read != 0)
	// {
	// 	nb_read = read(fd, buf, BUFFER_SIZE);
	// 	if (nb_read == -1)
	// 	{
	// 		printf("Erreur de lecture !\n");
	// 		return (1);
	// 	}
	// 	buf[nb_read] = '\0';
	// 	printf("%s", buf);
	// 	count ++;
	// }
	close(fd);
	return (0);
}
