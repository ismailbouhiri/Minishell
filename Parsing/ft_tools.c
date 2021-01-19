/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhiri <ibouhiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:11:39 by ibouhiri          #+#    #+#             */
/*   Updated: 2020/11/30 18:11:26 by ibouhiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_count(unsigned int n)
{
	int i;

	i = 1;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*conv(char *ptr, unsigned int s, int i, int c)
{
	while (s >= 10)
	{
		ptr[--i + c] = ((s % 10) + 48);
		s /= 10;
	}
	if (s < 10)
		ptr[--i + c] = ((s % 10) + 48);
	if (c == 1)
		ptr[--i + c] = 45;
	return (ptr);
}

char	*ft_itoa(int n)
{
	int				i;
	unsigned	int	s;
	int				c;
	char			*ptr;

	c = 0;
	if (n < 0)
	{
		c = 1;
		n *= -1;
	}
	s = n;
	i = ft_count(s);
	ptr = (char *)malloc(sizeof(char) * i + 1 + c);
	if (!ptr)
		return (NULL);
	ptr[i + c] = '\0';
	ptr = conv(ptr, s, i, c);
	return (ptr);
}

int		count_char(char *chars, char c)
{
	int i;

	i = 0;
	while (*chars == c)
		chars++;
	while (chars[i])
	{
		if (chars[i] == c)
			return (i);
		i++;
	}
	return (i);
}

int		count_word(char const *s, char c)
{
	int i;
	int word;

	i = 0;
	word = 1;
	if (s[i] == '\0')
		return (0);
	while (s[i] == c)
	{
		if (s[i + 1] == '\0')
			return (0);
		i++;
	}
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			word++;
		i++;
	}
	return (word);
}
