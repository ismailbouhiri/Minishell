/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 18:54:15 by mlasrite          #+#    #+#             */
/*   Updated: 2020/12/15 16:44:24 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../minishell.h"

char		**ft_free(char *str, int i, char **ptr)
{
	while (i >= 0)
	{
		free(str);
		i--;
	}
	free(ptr);
	return (0);
}

char		*ft_strdup(const char *s1)
{
	char	*s;
	int		len;
	int		i;

	len = 0;
	while (s1[len])
		len++;
	len++;
	s = malloc(len * sizeof(char));
	if (s == 0)
		return (0);
	i = -1;
	while (s1[++i])
		s[i] = s1[i];
	s[i] = '\0';
	return (s);
}

static int	readbytes(int fd, char **stock)
{
	char	*buff;
	int		bytes;
	char	*tmp;

	if (!(buff = (char *)malloc(BUFFER_SIZE + 1)))
		return (-1);
	bytes = read(fd, buff, BUFFER_SIZE);
	if (bytes > 0)
	{
		buff[bytes] = '\0';
		tmp = ft_strjoin(*stock, buff);
		if (!tmp)
			return (-1);
		free(*stock);
		*stock = tmp;
		free_backup(buff);
	}
	free(buff);
	return (bytes);
}

void		free_backup(char *buff)
{
	char	*tmp2;

	tmp2 = NULL;
	if (t_main.backup)
		tmp2 = t_main.backup;
	t_main.backup = ft_strjoin(tmp2, buff);
	if (tmp2)
	{
		free(tmp2);
		tmp2 = NULL;
	}
}

int			get_next_line(int fd, char **line)
{
	static char *stock;
	char		*index;
	int			bytes;

	if ((!stock && ((stock = ft_calloc(1, 1))) == NULL) || fd < 0 || !line)
		return (-1);
	while ((index = ft_strchr(stock, '\n')) == NULL)
	{
		bytes = readbytes(fd, &stock);
		if (bytes == 0 && !t_main.backup)
		{
			*line = ft_strdup(stock);
			free(stock);
			stock = NULL;
			return (0);
		}
		else if (bytes < 0)
			return (-1);
		index = ft_strchr(stock, '\n');
	}
	*line = ft_substr(stock, 0, index - stock);
	index = ft_strdup(index + 1);
	free(stock);
	stock = index;
	return (1);
}
