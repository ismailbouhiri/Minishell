/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhiri <ibouhiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 21:58:19 by mlasrite          #+#    #+#             */
/*   Updated: 2020/12/13 12:26:27 by ibouhiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int g_onetap;

int		execute(char **env, int start)
{
	t_var.tmp = g_hcmd;
	g_onetap = 0;
	while (t_var.tmp && g_onetap != start)
	{
		if (t_var.tmp->what == COMMAND)
			g_onetap += 1;
		if (g_onetap == start)
			break ;
		t_var.tmp = t_var.tmp->next;
	}
	g_onetap = 1;
	while (t_var.tmp && t_var.tmp->what != PIPE && t_var.tmp->what != 7)
	{
		if (execute_2(t_var.tmp) == 2831273)
			break ;
		if (t_var.tmp->what == COMMAND)
		{
			ft_step2(t_var.tmp);
			if (execute_commands(t_var.tmp, env) == 1)
				return (1);
		}
		t_var.tmp = t_var.tmp->next;
	}
	return (0);
}

int		execute_2(t_cmd *tmp)
{
	if (g_onetap)
	{
		g_onetap = 0;
		direct(tmp);
		if (g_ifin == 122)
		{
			dup2(g_savein, 0);
			g_ifin = 0;
			return (2831273);
		}
	}
	return (0);
}

int		execute_commands(t_cmd *tmp, char **env)
{
	if (ft_strcmp(tmp->cmd, "sort") == 0)
		g_issort = 1;
	else
		g_issort = 0;
	if (execute_commands2(tmp, env) == 1)
		return (1);
	dup2(g_savein, 0);
	dup2(g_saveout, 1);
	return (0);
}

void	execute_unset(t_cmd *tmp)
{
	while (tmp->next && tmp->next->what == STRING)
	{
		if (ft_check_equal_2(tmp->next->cmd))
			write(1, "not a valid identifier\n", 23);
		else
			ft_delete_nod(tmp->next->cmd);
		tmp = tmp->next;
	}
}

int		execute_pwd(void)
{
	char cwd[1000];

	if (getcwd(cwd, 1000) == NULL)
	{
		t_pipe.reti = 127;
		return (1);
	}
	else
	{
		dup_it_pipe();
		dup_it();
		t_pipe.reti = 0;
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
	}
	return (0);
}
