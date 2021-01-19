/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fichier_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhiri <ibouhiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 10:50:11 by ibouhiri          #+#    #+#             */
/*   Updated: 2020/12/13 11:41:44 by ibouhiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_condition(char *tmp, int i)
{
	if (tmp[i] == '\"' && !t_var.skip_slash && !t_var.single_quote)
		t_var.double_quote = (!t_var.double_quote) ? 1 : 0;
	if (tmp[i] == '\'' && !t_var.skip_slash && !t_var.double_quote)
		t_var.single_quote = (!t_var.single_quote) ? 1 : 0;
	if (tmp[i] != '\\' && t_var.skip_slash && tmp[i] != '>' && tmp[i] != '|'
	&& tmp[i] != ';' && tmp[i] != '<' && (tmp[i] != '>' && tmp[i + 1] != '>'))
		t_var.skip_slash = 0;
	if (tmp[i] == '\\')
		t_var.skip_slash = (!t_var.skip_slash) ? 1 : 0;
	if (g_hnew)
		if ((g_hnew->what == POINT_VIRGULE || g_hnew->what == PIPE)
		&& tmp[i] != '|' && tmp[i] != ';')
			t_var.cmd = 0;
}

void	ft_tableau(char *tab, char *tmp, int *i)
{
	if (!t_var.skip_slash && !t_var.single_quote && g_j == 0 &&
	!t_var.double_quote && (tmp[*i] == ';' || tmp[*i] == '<' || tmp[*i] == '>'
	|| tmp[*i] == '|'))
	{
		tab[g_j++] = tmp[(*i)++];
		if (tmp[*i] == '>')
			tab[g_j++] = tmp[(*i)++];
		tab[g_j] = '\0';
		g_j = 0;
		ft_link(tab);
		return ;
	}
	if (ft_normi(tab, tmp, i))
		return ;
	tab[g_j++] = tmp[*i];
	*i += 1;
}

void	ft_step1(char *line)
{
	int		i;
	char	*tmp;
	char	*tab;

	tab = (char *)malloc(sizeof(char) * (5049));
	tmp = trim_space(line);
	if (tmp[0] == ';' || tmp[0] == '>' || tmp[0] == '<' || tmp[0] == '|')
		t_var.cmd = 1;
	i = 0;
	while (tmp[i])
	{
		ft_condition(tmp, i);
		ft_tableau(tab, tmp, &i);
	}
	if (g_j > 0)
	{
		tab[g_j] = '\0';
		ft_link(tab);
	}
	free(tab);
	free(tmp);
}

void	ft_step2(t_cmd *tmp)
{
	char	*save;
	char	*tab;
	char	*new;

	tab = (char *)malloc(sizeof(char) * (5049));
	while (tmp && tmp->what != POINT_VIRGULE)
	{
		new = tmp->cmd;
		tmp->cmd = trim_space(tmp->cmd);
		free(new);
		ft_dollar(tab, tmp);
		save = tmp->cmd;
		tmp->cmd = ft_strdup(tab);
		free(save);
		tmp = tmp->next;
	}
	free(tab);
}

void	parser(char *line)
{
	ft_inis();
	ft_step1(line);
	rm_empty_nod();
	ft_rename_file();
	ft_corrector();
	ft_cmdorg();
	err_dir();
}
