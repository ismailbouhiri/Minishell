/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhiri <ibouhiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 11:20:16 by ibouhiri          #+#    #+#             */
/*   Updated: 2020/12/13 12:00:26 by ibouhiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		simple_cout(t_cmd *tmp, char *tab, int *i)
{
	int		save;
	char	*cmd;

	cmd = tmp->cmd;
	*i += (cmd[*i]) ? 1 : 0;
	save = *i;
	while (cmd[*i] != '\'' && cmd[*i])
	{
		tab[g_j++] = cmd[*i];
		*i += (cmd[*i]) ? 1 : 0;
	}
	if (save == *i && g_j == 0 && cmd[*i + 1] == '\0' && tmp->what == 1)
		tab[g_j++] = '1';
	*i += (cmd[*i]) ? 1 : 0;
	return (1);
}

int		double_cout(t_cmd *tmp, char *tab, int *i)
{
	char	*cmd;

	cmd = tmp->cmd;
	t_var.skip_slash = 0;
	*i += (cmd[*i]) ? 1 : 0;
	g_s = *i;
	t_var.double_quote = 1;
	while (cmd[*i])
	{
		if (cmd[*i] == '\"' && !t_var.skip_slash)
		{
			if (g_s == *i && !g_j && cmd[*i + 1] == '\0' && tmp->what == 1)
				tab[g_j++] = '1';
			*i += (cmd[*i]) ? 1 : 0;
			break ;
		}
		if (cmd[*i] == '$' && !t_var.skip_slash && cmd[*i + 1] != '\0' &&
		cmd[*i + 1] != '\"' && cmd[*i + 1] != '\\' && cmd[*i + 1] != '\'')
			if (replace_dollar(cmd, tab, i))
				continue;
		ft_countinue(cmd, i);
		tab[g_j++] = cmd[*i];
		*i += (cmd[*i] != '\0') ? 1 : 0;
	}
	return (1);
}

int		replace_dollar(char *cmd, char *tab, int *i)
{
	char	tmp[5024];
	int		j;
	char	*tmp_env;
	int		save;
	int		check;

	j = 0;
	check = (cmd[0] == '~' && cmd[1] == '\0') ? 1 : 0;
	if (cmd[0] == '~' && cmd[1] == '\0')
		cmd = "$HOME";
	save = *i + 1;
	if (cmd[save] == '?')
		return (ft_ret(tab, i));
	while (ft_isalnum(cmd[save]) || cmd[save] == '_')
		tmp[j++] = cmd[save++];
	tmp[j] = '\0';
	tmp_env = ft_find_value_env(tmp);
	if (tmp_env)
		ft_strcpy_dollar(tab + g_j, tmp_env);
	g_j += (tmp_env) ? ft_strlen(tmp_env) : 0;
	*i += (!check) ? j + 1 : 1;
	return (1);
}

char	*trim_space(char *cmd)
{
	int		len;
	char	*ptr;
	int		j;

	t_var.i = 0;
	j = 0;
	if (cmd[0] == '\0')
		return (ft_strdup(cmd));
	len = ft_strlen(cmd);
	while ((cmd[t_var.i] == ' ' || cmd[t_var.i] == '\t') && cmd[t_var.i])
		t_var.i++;
	len -= 1;
	while ((cmd[len] == ' ' || cmd[len] == '\t') && len > 0)
	{
		if (cmd[len - 1] == '\\' && cmd[len] == ' ')
			break ;
		len--;
	}
	len += 1;
	len = (len - t_var.i < 0) ? t_var.i : len;
	ptr = (char *)malloc(sizeof(char) * (len + 1 - t_var.i));
	while (t_var.i < len && cmd[t_var.i])
		ptr[j++] = cmd[t_var.i++];
	ptr[j] = '\0';
	return (ptr);
}

void	free_nod(void)
{
	t_nod	*tmp;

	while (g_head)
	{
		tmp = g_head->next;
		free(g_head->key);
		free(g_head->value);
		free(g_head);
		g_head = NULL;
		g_head = tmp;
	}
}
