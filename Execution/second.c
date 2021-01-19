/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 20:26:23 by mlasrite          #+#    #+#             */
/*   Updated: 2020/12/12 11:07:11 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipes_5(void)
{
	if (t_pipe.i == 0 && t_pipe.count_pipes > 0)
		close(t_pipe.fd[0][1]);
	else if (t_pipe.i == t_pipe.count_pipes && t_pipe.count_pipes > 0)
		close(t_pipe.fd[t_pipe.i - 1][0]);
	else if (t_pipe.i != t_pipe.count_pipes && t_pipe.count_pipes > 0)
	{
		close(t_pipe.fd[t_pipe.i - 1][0]);
		close(t_pipe.fd[t_pipe.i][1]);
	}
	t_pipe.i += 1;
	if (t_pipe.ispipeinfront == 2 || g_command == t_pipe.k)
	{
		while (t_pipe.u < t_pipe.waits)
		{
			wait(&t_pipe.reti);
			t_pipe.u += 1;
		}
		t_pipe.reti = WEXITSTATUS(t_pipe.reti);
	}
}

void	allocate_pipe(int k)
{
	int i;

	i = 0;
	t_pipe.count_pipes = ft_lstcountpipe(k);
	t_pipe.fd = malloc(sizeof(int *) * (t_pipe.count_pipes + 1));
	t_pipe.fd[t_pipe.count_pipes] = NULL;
	while (i < t_pipe.count_pipes)
	{
		t_pipe.fd[i] = malloc(sizeof(int) * (2 + 1));
		t_pipe.fd[i][2] = '\0';
		pipe(t_pipe.fd[i++]);
	}
}

int		checkpv(int max)
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
			if (save == POINT_VIRGULE)
				return (1);
			return (0);
		}
		save = tmp->what;
		tmp = tmp->next;
	}
	return (0);
}

void	free_old(void)
{
	int t;

	t = 0;
	while (t < t_pipe.count_pipes)
	{
		close(t_pipe.fd[t][0]);
		close(t_pipe.fd[t][1]);
		free(t_pipe.fd[t++]);
	}
	free(t_pipe.fd);
}

void	ft_strcpy_dollar(char *dst, char *src)
{
	int i;

	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
}
