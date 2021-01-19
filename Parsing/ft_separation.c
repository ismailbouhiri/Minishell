/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_separation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhiri <ibouhiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 14:36:32 by ibouhiri          #+#    #+#             */
/*   Updated: 2020/12/13 12:26:23 by ibouhiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_lst(void)
{
	t_cmd *tmp;

	while (g_hcmd)
	{
		tmp = g_hcmd->next;
		free(g_hcmd->cmd);
		free(g_hcmd);
		g_hcmd = tmp;
	}
}

int		check(char *tab)
{
	if (t_var.cmd == 0)
		return (COMMAND);
	else if (tab[0] == '|' && !t_var.pipe)
		return (PIPE);
	else if (tab[0] == '>' && tab[1] != '>' && !t_var.rediction_right)
		return (REDIRECTION_RIGHT);
	else if (tab[0] == '<' && !t_var.rediction_left)
		return (REDIRECTION_LEFT);
	else if (tab[0] == '>' && tab[1] == '>' && !t_var.doulbe_rediction)
		return (DOUBLE_REDICTION);
	else if (tab[0] == ';' && !t_var.point_virgule)
		return (POINT_VIRGULE);
	else
		return (STRING);
	return (0);
}

int		ft_countinue(char *cmd, int *i)
{
	int save;

	save = *i;
	if (t_var.double_quote)
	{
		if (cmd[*i] == '\\' && (cmd[*i + 1] == '\"' ||
		cmd[*i + 1] == '\\' || cmd[*i + 1] == '$'))
			*i += 1;
		else if (cmd[*i] == '\\' && (save != *i))
			t_var.skip_slash = (t_var.skip_slash) ? 0 : 1;
	}
	else
	{
		if (cmd[*i] == '\\' && !t_var.skip_slash)
			*i += 1;
		else if (cmd[*i] == '\\')
			t_var.skip_slash = (t_var.skip_slash) ? 0 : 1;
	}
	return (0);
}

void	ft_dollar(char *tab, t_cmd *tmp)
{
	int		i;
	char	*cmd;

	i = 0;
	g_j = 0;
	t_var.skip_slash = 0;
	cmd = tmp->cmd;
	while (cmd[i])
	{
		t_var.double_quote = 0;
		if (cmd[i] == '\'' && !t_var.skip_slash)
			if (simple_cout(tmp, tab, &i))
				continue;
		if (cmd[i] == '\"' && !t_var.skip_slash)
			if (double_cout(tmp, tab, &i))
				continue;
		if (((cmd[i] == '$' && !t_var.skip_slash && cmd[i + 1] != '\0' &&
		cmd[i + 1] != '\\') || (cmd[0] == '~' && cmd[1] == '\0')))
			if (replace_dollar(cmd, tab, &i))
				continue;
		ft_countinue(cmd, &i);
		tab[g_j++] = cmd[i];
		i += (cmd[i]) ? 1 : 0;
	}
	tab[g_j] = '\0';
}
