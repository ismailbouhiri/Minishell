/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 20:08:50 by mlasrite          #+#    #+#             */
/*   Updated: 2020/12/10 11:36:02 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		count_cmd(void)
{
	t_cmd	*tmp;
	int		c;

	tmp = g_hcmd;
	c = 0;
	while (tmp)
	{
		if (tmp->what == COMMAND)
			c += 1;
		tmp = tmp->next;
	}
	return (c);
}

int		beforepipe(int max)
{
	t_cmd	*tmp;
	int		c;
	int		save;

	tmp = g_hcmd;
	c = 0;
	save = 0;
	while (tmp)
	{
		if (tmp->what == COMMAND)
			c += 1;
		if (c == max)
		{
			if (save == PIPE)
				return (1);
			return (0);
		}
		save = tmp->what;
		tmp = tmp->next;
	}
	return (0);
}

int		check_pipe(int start)
{
	t_cmd	*tmp;
	int		count;

	tmp = g_hcmd;
	count = 0;
	while (tmp && count != start)
	{
		if (tmp->what == COMMAND)
			count += 1;
		if (count == start)
			break ;
		tmp = tmp->next;
	}
	while (tmp)
	{
		if (tmp->what == POINT_VIRGULE)
			return (2);
		else if (tmp->what == PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		ft_lstcountpipe(int k)
{
	int		len;
	t_cmd	*lst;

	len = 0;
	lst = g_hcmd;
	help_lstcountpipe(&lst, k);
	while (lst)
	{
		if (lst->what == PIPE)
			len++;
		if (lst->what == POINT_VIRGULE && len != 0)
			break ;
		lst = lst->next;
	}
	return (len);
}

void	help_lstcountpipe(t_cmd **lst, int k)
{
	int		count;

	count = 0;
	while ((*lst) && count != k)
	{
		if ((*lst)->what == COMMAND)
			count += 1;
		if (count == k)
		{
			(*lst) = (*lst)->next;
			if ((*lst))
				if ((*lst)->what == POINT_VIRGULE)
					(*lst) = (*lst)->next;
			break ;
		}
		(*lst) = (*lst)->next;
		if ((*lst))
			if ((*lst)->what == POINT_VIRGULE)
				(*lst) = (*lst)->next;
	}
}
