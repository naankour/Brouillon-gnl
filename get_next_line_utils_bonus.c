/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:22:42 by naankour          #+#    #+#             */
/*   Updated: 2024/12/03 15:43:24 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;

	new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[i])
			new[j++] = s1[i++];
	}
	i = 0;
	if (s2)
	{
		while (s2[i])
			new[j++] = s2[i++];
	}
	new[j] = '\0';
	free(s1);
	return (new);
}

char	*ft_strdup(char *src)
{
	char	*dest;
	int		i;

	i = 0;
	if (!src || src[0] == '\0')
		return (NULL);
	if (ft_strchr(src, '\n') == 1)
		dest = (char *)malloc(sizeof (char) * (ft_strlen(src) + 2));
	if (ft_strchr(src, '\n') == 0)
		dest = (char *)malloc(sizeof (char) * (ft_strlen(src) + 1));
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
	updated_buffer = malloc(sizeof(char) * ((ft_strlen(buffer)- i + 1)));
	if (!updated_buffer)
	{
		free (buffer);
		return (NULL);
	}
	index = 0;
	while (buffer[i] != '\0')
		updated_buffer[index++] = buffer[i++];
	updated_buffer[index] = '\0';
	free(buffer);
	return (updated_buffer);
}
