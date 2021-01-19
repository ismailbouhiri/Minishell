/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils03.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhiri <ibouhiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 18:15:24 by mlasrite          #+#    #+#             */
/*   Updated: 2020/12/12 09:38:49 by ibouhiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_it_pipe(void)
{
	if (g_canidup == 1)
	{
		if (t_pipe.i == 0 && t_pipe.count_pipes > 0)
		{
			dup2(t_pipe.fd[0][1], 1);
			close(t_pipe.fd[0][0]);
		}
		else if (t_pipe.i == t_pipe.count_pipes && t_pipe.count_pipes > 0)
			dup2(t_pipe.fd[t_pipe.i - 1][0], 0);
		else if (t_pipe.count_pipes > 0)
		{
			dup2(t_pipe.fd[t_pipe.i - 1][0], 0);
			dup2(t_pipe.fd[t_pipe.i][1], 1);
			close(t_pipe.fd[t_pipe.i][0]);
		}
	}
}

void	ft_norminetteexit(void)
{
	if (beforepipe(t_pipe.k) != 1 && check_pipe(t_pipe.k) != 1)
		write(1, "exit\n", 5);
	write(1, "exit: too many arguments\n", 25);
}

int		ft_check_key(char *ptr)
{
	int i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == '=')
			break ;
		else if (!((ptr[i] >= '0' && ptr[i] <= '9') || (ptr[i] >= 'a' &&
		ptr[i] <= 'z') || (ptr[i] >= 'A' && ptr[i] <= 'Z') || ptr[i] == '_'))
			return (1);
		i++;
	}
	return (0);
}

void	envy(t_cmd *tmp)
{
	if (tmp && (!tmp->next || (tmp->next && (tmp->next->what == PIPE
	|| tmp->next->what == POINT_VIRGULE))))
		ft_print_nod();
	else
	{
		write(1, "No such file or directory\n", 26);
	}
}

int		execute_commands2(t_cmd *tmp, char **env)
{
	if (ft_strcmp(tmp->cmd, "echo") == 0)
		echo(tmp);
	else if ((ft_strcmp(tmp->cmd, "cd")) == 0)
	{
		if (execute_cd(tmp) == 1)
			return (1);
	}
	else if (ft_strcmp(tmp->cmd, "pwd") == 0)
	{
		if (execute_pwd() == 1)
			return (1);
	}
	else if (ft_strcmp(tmp->cmd, "env") == 0)
		envy(tmp);
	else if (ft_strcmp(tmp->cmd, "export") == 0)
		export(tmp);
	else if (ft_strcmp(tmp->cmd, "unset") == 0)
		execute_unset(tmp);
	else if (ft_strcmp(tmp->cmd, "exit") == 0)
		exit_entry(tmp);
	else
		search_it(tmp, env);
	return (0);
}
