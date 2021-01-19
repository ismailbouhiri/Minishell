/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 10:23:22 by ibouhiri          #+#    #+#             */
/*   Updated: 2020/12/15 16:46:59 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	println(int key)
{
	if (key == SIGQUIT)
		g_ctrl_c = 0;
	if (key == SIGINT)
		g_ctrl_c = 1;
	if (key == SIGINT && g_stillexec == 0)
	{
		if (t_main.backup && g_linelen == 0)
		{
			g_linelen = ft_strlen(t_main.backup);
			free(t_main.backup);
			t_main.backup = NULL;
		}
		else
		{
			g_linelen += ft_strlen(t_main.backup);
			free(t_main.backup);
			t_main.backup = NULL;
		}
		write(1, "\n> Minishel : ", 14);
	}
	if (key == SIGQUIT && g_stillexec == 1 && g_issort == 0)
		write(1, "Quit: 3\n", 8);
	else if (key == SIGQUIT && g_stillexec == 0)
		write(1, "\b\b", 2);
}

int		ft_check_equal_2(char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (1);
		i += 1;
	}
	return (0);
}

void	send_to_entry(char **env)
{
	parser(t_main.line);
	if (t_main.ret == 1 && entry(env) == 1 && !g_erreur)
		write(1, "Error\n", 6);
	free_lst();
}

void	prompt(char **env)
{
	while (1)
	{
		write(1, "> Minishel : ", 13);
		t_main.ret = get_next_line(0, &t_main.line);
		if (t_main.ret == 0)
		{
			write(1, "exit", 4);
			free_nod();
			free(t_main.line);
			t_main.line = NULL;
			break ;
		}
		if (t_main.ret == 1)
			override_line(env);
		free(t_main.line);
		t_main.line = NULL;
		free(t_main.backup);
		t_main.backup = NULL;
		g_isin = 0;
		g_canidup = 0;
		g_linelen = 0;
		g_isout = 0;
	}
}

int		main(int argc, char **argv, char **env)
{
	argc = 0;
	argv = NULL;
	t_main.backup = NULL;
	t_pipe.reti = 0;
	g_stillexec = 0;
	g_linelen = 0;
	g_ctrl_c = 0;
	g_isin = 0;
	g_isout = 0;
	g_canidup = 0;
	g_issort = 0;
	signal(SIGINT, println);
	signal(SIGQUIT, println);
	ft_collecte_env(env);
	prompt(env);
	free_nod();
	return (0);
}
