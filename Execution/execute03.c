/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute03.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhiri <ibouhiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 20:35:07 by mlasrite          #+#    #+#             */
/*   Updated: 2020/12/12 09:33:02 by ibouhiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		direct_l(t_cmd *p)
{
	int ret;

	ret = 0;
	if (p->what == FILE)
	{
		ret = direct_l_2(p);
		if (ret == -845628)
			return (1);
		else if (ret != -648923)
		{
			g_isin = 1;
			g_in = ret;
		}
	}
	return (0);
}

int		direct_l_2(t_cmd *p)
{
	int		fd;

	if ((fd = open(p->cmd, O_RDWR)) == -1)
	{
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		write(1, "\n", 1);
		g_ifin = 122;
		return (-845628);
	}
	if (g_count2 > 1)
	{
		g_count2--;
		close(fd);
	}
	else
		return (fd);
	return (-648923);
}

int		count_r_a(t_cmd *tmp)
{
	t_cmd	*p;
	int		count;

	count = 0;
	p = tmp;
	while (p && p->what != PIPE && p->what != POINT_VIRGULE)
	{
		if (p->what == REDIRECTION_RIGHT || p->what == DOUBLE_REDICTION)
		{
			p = p->next;
			if (p->what == FILE)
				count += 1;
		}
		p = p->next;
	}
	return (count);
}

int		count_l(t_cmd *tmp)
{
	t_cmd	*p;
	int		count;

	count = 0;
	p = tmp;
	while (p && p->what != PIPE && p->what != POINT_VIRGULE)
	{
		if (p->what == REDIRECTION_LEFT)
		{
			p = p->next;
			if (p->what == FILE)
				count += 1;
		}
		p = p->next;
	}
	return (count);
}

int		path_exist(void)
{
	t_nod *tmp;

	tmp = g_head;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
