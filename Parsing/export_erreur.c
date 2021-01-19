/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_erreur.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhiri <ibouhiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:57:27 by ibouhiri          #+#    #+#             */
/*   Updated: 2020/12/13 14:26:16 by ibouhiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	err_dir(void)
{
	t_cmd *tmp;

	tmp = g_hcmd;
	while (tmp)
	{
		if (tmp->what == 4 || tmp->what == 5 || tmp->what == 6 ||
		tmp->what == 3 || tmp->what == 7)
		{
			if (tmp->what != 7 && tmp->next == NULL)
			{
				err_dec();
				break ;
			}
			tmp = tmp->next;
			if (tmp && (tmp->what == 4 || tmp->what == 5 || tmp->what == 6 ||
			tmp->what == 3 || tmp->what == 7 || g_hcmd->what == 7))
			{
				err_dec();
				break ;
			}
		}
		tmp = (tmp) ? tmp->next : tmp;
	}
}

void	ft_rename_file(void)
{
	t_cmd *tmp;

	tmp = g_hcmd;
	while (tmp)
	{
		if ((tmp->what == REDIRECTION_RIGHT || tmp->what == REDIRECTION_LEFT ||
		tmp->what == DOUBLE_REDICTION) && tmp->next != NULL &&
		tmp->next->what == STRING)
			tmp->next->what = FILE;
		tmp = (tmp) ? tmp->next : tmp;
	}
}

void	rm_empty_nod(void)
{
	t_cmd *tmp;
	t_cmd *save;

	tmp = g_hcmd;
	if (!g_hcmd)
		return ;
	while (tmp)
	{
		save = tmp->next;
		if (!save)
			break ;
		if ((save->cmd[0] == '\0') || (save->cmd[0] == ' ' &&
		save->cmd[1] == '\0'))
		{
			tmp->next = save->next;
			free(save->cmd);
			free(save);
			save = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}
