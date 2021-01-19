/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 21:46:19 by mlasrite          #+#    #+#             */
/*   Updated: 2020/12/12 20:27:59 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		entry(char **env)
{
	t_pipe.u = 0;
	t_pipe.i = 0;
	t_pipe.ispipebehind = 0;
	t_pipe.ispvbehind = 0;
	t_pipe.waits = 0;
	t_pipe.k = 1;
	if (pipes(env) == 1)
		return (1);
	return (0);
}

int		pipes(char **env)
{
	int		ret;

	ret = 0;
	allocate_pipe(t_pipe.k);
	g_command = count_cmd();
	while (1)
	{
		t_pipe.ispipeinfront = check_pipe(t_pipe.k);
		t_pipe.ispipebehind = beforepipe(t_pipe.k);
		t_pipe.ispvbehind = checkpv(t_pipe.k);
		g_canidup = 0;
		pipes_2();
		ret = pipes_3(env);
		if (ret == 1)
			return (1);
		else if (ret == 2)
			break ;
		else if (ret == 3)
			return (0);
		t_pipe.k += 1;
	}
	free_old();
	return (0);
}

void	pipes_2(void)
{
	if (t_pipe.ispvbehind == 1 && t_pipe.ispipebehind == 0 \
	&& t_pipe.count_pipes > 0)
	{
		free_old();
		t_pipe.i = 0;
		allocate_pipe(t_pipe.k);
	}
}

int		pipes_3(char **env)
{
	if (t_pipe.ispipeinfront == 0 && t_pipe.ispipebehind == 0)
	{
		if (execute(env, t_pipe.k) == 1)
			return (1);
		return (2);
	}
	else if (t_pipe.ispipeinfront == 2 && t_pipe.ispipebehind == 0)
	{
		if (execute(env, t_pipe.k) == 1)
			return (1);
	}
	else if (t_pipe.i < t_pipe.count_pipes + 1 || t_pipe.ispipebehind == 1)
	{
		if (pipes_4(env) == 1)
			return (1);
	}
	if (g_command == t_pipe.k)
	{
		free_old();
		return (3);
	}
	return (0);
}

int		pipes_4(char **env)
{
	t_pipe.waits += 1;
	t_pipe.pid = fork();
	if (t_pipe.pid < 0)
		return (1);
	else if (t_pipe.pid == 0)
	{
		g_canidup = 1;
		if (execute(env, t_pipe.k) == 1)
			return (1);
		exit(0);
	}
	pipes_5();
	return (0);
}
