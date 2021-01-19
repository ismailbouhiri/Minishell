/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhiri <ibouhiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 20:35:03 by mlasrite          #+#    #+#             */
/*   Updated: 2020/12/12 09:32:55 by ibouhiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		execute_cd(t_cmd *tmp)
{
	if (tmp->next != NULL)
	{
		if (chdir(tmp->next->cmd) == -1)
		{
			t_pipe.reti = 1;
			write(1, "No such file or directory\n", 26);
			return (0);
		}
		else
			t_pipe.reti = 0;
	}
	else
	{
		if (chdir(ft_find_value_env("HOME")) == -1)
		{
			t_pipe.reti = 1;
			return (1);
		}
		else
			t_pipe.reti = 0;
	}
	return (0);
}

void	direct(t_cmd *tmp)
{
	int c_l;
	int c_r_a;

	c_l = count_l(tmp);
	c_r_a = count_r_a(tmp);
	if (c_r_a > 0 || c_l > 0)
	{
		direct_r_a(tmp);
		g_saveout = dup(1);
		g_savein = dup(0);
	}
}

void	direct_r_a(t_cmd *tmp)
{
	t_cmd	*p;
	int		fd;
	int		ret;

	g_count = count_r_a(tmp);
	g_count2 = count_l(tmp);
	p = tmp;
	while (p && p->what != PIPE && p->what != POINT_VIRGULE)
	{
		if (g_count2 > 0 && p->what == REDIRECTION_LEFT)
		{
			p = p->next;
			if ((ret = direct_l(p)) == 1)
				break ;
		}
		if (g_count > 0 && (fd = direct_r_a_2(p, fd)) != -54784)
		{
			g_isout = 1;
			g_out = fd;
		}
		p = p->next;
	}
}

int		direct_r_a_2(t_cmd *p, int fd)
{
	int ret;

	ret = 0;
	if (p->what == REDIRECTION_RIGHT || p->what == DOUBLE_REDICTION)
	{
		if ((ret = direct_r_a_3(p, fd)) != -54784)
			return (ret);
		if (p->what == DOUBLE_REDICTION)
		{
			p = p->next;
			if (p->what == FILE)
			{
				fd = open(p->cmd, O_RDWR | O_CREAT | O_APPEND, 0644);
				if (g_count > 1)
				{
					g_count--;
					close(fd);
				}
				else
					return (fd);
			}
		}
	}
	return (-54784);
}

int		direct_r_a_3(t_cmd *p, int fd)
{
	if (p->what == REDIRECTION_RIGHT)
	{
		p = p->next;
		if (p->what == FILE)
		{
			fd = open(p->cmd, O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (g_count > 1)
			{
				g_count--;
				close(fd);
			}
			else
				return (fd);
		}
	}
	return (-54784);
}
