/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_norm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhiri <ibouhiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:43:42 by ibouhiri          #+#    #+#             */
/*   Updated: 2020/12/13 14:15:15 by ibouhiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_normi(char *tab, char *tmp, int *i)
{
	if ((tmp[*i] == ' ' || tmp[*i] == '\t' || tmp[*i + 1] == ';' ||
	tmp[*i + 1] == '<' || tmp[*i + 1] == '>' || tmp[*i + 1] == '|')
	&& !t_var.single_quote && !t_var.double_quote && !t_var.skip_slash)
	{
		if (tmp[*i] != ' ' && tmp[*i] != '\t')
			tab[g_j++] = tmp[*i];
		*i += 1;
		tab[g_j] = '\0';
		g_j = 0;
		ft_link(tab);
		return (1);
	}
	if (t_var.skip_slash && tmp[*i] == '>' && !t_var.double_quote
	&& !t_var.single_quote)
	{
		tab[g_j++] = tmp[(*i)++];
		tab[g_j] = '\0';
		g_j = 0;
		ft_link(tab);
		return (1);
	}
	return (0);
}

void	add_back(t_sorted *ptr)
{
	t_sorted *tmp;

	tmp = g_shead;
	if (!g_shead)
	{
		g_shead = ptr;
		return ;
	}
	while (tmp)
	{
		if (!tmp->next)
		{
			tmp->next = ptr;
			return ;
		}
		tmp = tmp->next;
	}
}

void	free_shead(void)
{
	t_sorted *tmp2;

	while (g_shead)
	{
		tmp2 = g_shead->next;
		free(g_shead->key);
		g_shead->key = NULL;
		free(g_shead->value);
		g_shead->value = NULL;
		free(g_shead);
		g_shead = tmp2;
	}
}

void	dup_it(void)
{
	if (g_isout == 1)
	{
		dup2(g_out, 1);
		close(g_out);
	}
	if (g_isin == 1)
	{
		dup2(g_in, 0);
		close(g_in);
	}
}

void	override_line(char **env)
{
	char	*tmp2;

	tmp2 = NULL;
	if (ft_strlen(t_main.line) >= g_linelen && g_linelen > 0)
	{
		tmp2 = t_main.line;
		t_main.line = ft_strdup(tmp2 + g_linelen);
		free(tmp2);
		tmp2 = NULL;
	}
	send_to_entry(env);
}
