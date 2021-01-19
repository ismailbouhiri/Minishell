/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhiri <ibouhiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 02:18:19 by mlasrite          #+#    #+#             */
/*   Updated: 2020/12/13 14:28:20 by ibouhiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(t_cmd *tmp)
{
	t_cmd	*p;

	p = tmp;
	dup_it_pipe();
	dup_it();
	if (ft_lstsize(tmp) == 1)
		write(1, "\n", 1);
	else if (ft_lstsize(tmp) == 2)
	{
		if (!(tmp->next->cmd[0] == '-' && tmp->next->cmd[1]
		== 'n' && tmp->next->cmd[2] == '\0'))
			while (p && p->what != PIPE && p->what != POINT_VIRGULE)
			{
				if (p->what == STRING)
				{
					write(1, p->cmd, ft_strlen(p->cmd));
					write(1, "\n", 1);
				}
				p = p->next;
			}
	}
	else
		help_echo(tmp);
	t_pipe.reti = 0;
}

void	help_echo(t_cmd *tmp)
{
	if (tmp->next->cmd[0] == '-' && tmp->next->cmd[1]
	== 'n' && tmp->next->cmd[2] == '\0')
	{
		tmp = tmp->next;
		while (tmp->next && tmp->next->what == STRING)
		{
			if (!tmp->next->cmd[0])
			{
				tmp = tmp->next;
				continue;
			}
			write(1, tmp->next->cmd, ft_strlen(tmp->next->cmd));
			tmp = tmp->next;
			if (tmp->next && tmp->next->what != POINT_VIRGULE)
				write(1, " ", 1);
		}
	}
	else
		help_echo2(tmp);
}

void	help_echo2(t_cmd *tmp)
{
	while (tmp->next && tmp->next->what == STRING)
	{
		if (!tmp->next->cmd[0])
		{
			tmp = tmp->next;
			continue;
		}
		write(1, tmp->next->cmd, ft_strlen(tmp->next->cmd));
		tmp = tmp->next;
		if (tmp->next)
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}

int		ft_lstsize(t_cmd *lst)
{
	int len;

	len = 0;
	while (lst && lst->what != POINT_VIRGULE && lst->what != PIPE)
	{
		if (lst->what == COMMAND || lst->what == STRING)
			len++;
		lst = lst->next;
	}
	return (len);
}
