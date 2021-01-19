/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_slash.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhiri <ibouhiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 18:28:02 by ibouhiri          #+#    #+#             */
/*   Updated: 2020/12/13 12:25:46 by ibouhiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_inis(void)
{
	g_hcmd = NULL;
	g_hnew = NULL;
	g_shead = NULL;
	g_j = 0;
	t_var.cmd = 0;
	t_var.skip_slash = 0;
	t_var.pipe = 0;
	t_var.point_virgule = 0;
	t_var.double_quote = 0;
	t_var.single_quote = 0;
	t_var.rediction_left = 0;
	t_var.rediction_right = 0;
	t_var.doulbe_rediction = 0;
	t_var.i = 0;
	g_erreur = 0;
}

int		ft_ret(char *tab, int *i)
{
	char *tmp_env;

	tmp_env = ft_itoa(t_pipe.reti);
	ft_strcpy_dollar(tab + g_j, tmp_env);
	g_j += (tmp_env) ? ft_strlen(tmp_env) : 0;
	*i += 2;
	free(tmp_env);
	return (1);
}

void	ft_corrector(void)
{
	t_cmd	*tmp;

	tmp = g_hcmd;
	while (tmp)
	{
		if (tmp->what == PIPE || tmp->what == POINT_VIRGULE)
			if (tmp->next && tmp->next->what == STRING)
				tmp->next->what = COMMAND;
		tmp = tmp->next;
	}
}

void	ft_norm(t_cmd *firstcmd, t_cmd *firstredir, t_cmd *cmd, t_cmd *copycmd)
{
	if (cmd != g_hcmd && cmd->next != firstcmd)
	{
		cmd->next = firstcmd;
		copycmd->next = firstcmd->next;
		firstcmd->next = NULL;
		firstcmd->next = firstredir;
	}
	if (cmd == g_hcmd && cmd != firstcmd)
	{
		g_hcmd = NULL;
		g_hcmd = firstcmd;
		copycmd->next = firstcmd->next;
		firstcmd->next = NULL;
		firstcmd->next = firstredir;
	}
}

int		ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
