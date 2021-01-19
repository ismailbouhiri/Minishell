/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_directions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhiri <ibouhiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:46:31 by ibouhiri          #+#    #+#             */
/*   Updated: 2020/12/11 16:42:05 by ibouhiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_fixdirections(t_cmd *cmd, t_cmd *firstredir)
{
	t_cmd	*tmp;

	tmp = NULL;
	t_var.cmd = 0;
	g_hnew = ft_lstnew_cmd(ft_strdup("echo"), check("echo"));
	ft_lstadd_back_cmd(&tmp, g_hnew);
	t_var.cmd = 1;
	g_hnew = ft_lstnew_cmd(ft_strdup("-n"), check("-n"));
	ft_lstadd_back_cmd(&tmp, g_hnew);
	if (cmd == g_hcmd)
	{
		g_hcmd = NULL;
		g_hcmd = tmp;
		ft_lstadd_back_cmd(&g_hcmd, firstredir);
		return ;
	}
	cmd->next = NULL;
	ft_lstadd_back_cmd(&cmd, tmp);
	ft_lstadd_back_cmd(&cmd->next->next, firstredir);
}

void	ft_cmdorg(void)
{
	t_cmd	*cmd;
	t_cmd	*findcmd;
	t_cmd	*firstcmd;
	t_cmd	*firstredir;

	cmd = g_hcmd;
	while (cmd)
	{
		findcmd = (cmd == g_hcmd) ? cmd : cmd->next;
		firstcmd = NULL;
		firstredir = NULL;
		t_var.directions = 0;
		t_var.command = 0;
		while (findcmd && findcmd->what != 3 && findcmd->what != 7)
		{
			ft_command_var(findcmd, &firstcmd, &firstredir);
			findcmd = findcmd->next;
		}
		if (t_var.directions && t_var.command)
			ft_swapcmd(cmd, firstcmd, firstredir);
		if (t_var.directions && !t_var.command)
			ft_fixdirections(cmd, firstredir);
		cmd = (cmd == findcmd) ? cmd->next : findcmd;
	}
}

void	ft_swapcmd(t_cmd *cmd, t_cmd *firstcmd, t_cmd *firstredir)
{
	t_cmd *copycmd;

	copycmd = (cmd == g_hcmd) ? cmd : cmd->next;
	firstcmd->what = COMMAND;
	while (copycmd && copycmd->what != PIPE && copycmd->what != POINT_VIRGULE)
	{
		if (copycmd->next == firstcmd || copycmd == firstcmd)
		{
			ft_norm(firstcmd, firstredir, cmd, copycmd);
			ft_addstr(firstcmd, firstredir);
			return ;
		}
		copycmd = copycmd->next;
	}
}

void	ft_addstr(t_cmd *firstcmd, t_cmd *firdir)
{
	t_cmd	*copycmd;
	t_cmd	*findarg;

	while (firstcmd && firstcmd->next && firstcmd->next->what == STRING)
		firstcmd = firstcmd->next;
	copycmd = firstcmd->next;
	while (copycmd && copycmd->what != PIPE && copycmd->what != POINT_VIRGULE)
	{
		findarg = copycmd->next;
		if (findarg && findarg->what == STRING)
		{
			copycmd->next = findarg->next;
			firstcmd->next = findarg;
			findarg->next = NULL;
			firstcmd = firstcmd->next;
			firstcmd->next = firdir;
		}
		copycmd = (copycmd->next != findarg) ? copycmd : copycmd->next;
	}
}

char	**ft_split(char const *s, char c)
{
	int		len;
	int		i;
	char	**string;
	char	*ptr;

	if (s == NULL)
		return (NULL);
	len = 0;
	ptr = (char*)s;
	if (!(string = (char **)malloc((count_word(s, c) + 1) * sizeof(char *))))
		return (NULL);
	while (count_word(s, c) > len)
	{
		i = 0;
		if (!(string[len] = (char *)malloc((count_char(ptr, c) + 1) *
		sizeof(char))))
			return (ft_free(string[len], len, string));
		while (*ptr == c)
			ptr++;
		while (*ptr != c && *ptr)
			string[len][i++] = *ptr++;
		string[len++][i] = '\0';
	}
	string[len] = 0;
	return (string);
}
