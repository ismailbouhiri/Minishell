/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 13:22:35 by ibouhiri          #+#    #+#             */
/*   Updated: 2020/12/08 14:41:37 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_nod	*ft_lstnew(char *key, char *value)
{
	t_nod *tmp;

	if (!(tmp = (t_nod *)malloc(sizeof(t_nod))))
		return (NULL);
	tmp->key = key;
	tmp->value = value;
	tmp->next = NULL;
	return (tmp);
}

t_cmd	*ft_lstnew_cmd(char *cmd, int what)
{
	t_cmd *tmp;

	if (!(tmp = (t_cmd *)malloc(sizeof(t_cmd))))
		return (NULL);
	tmp->cmd = cmd;
	tmp->what = what;
	tmp->next = NULL;
	t_var.cmd = 1;
	return (tmp);
}

void	ft_lstadd_back_cmd(t_cmd **head, t_cmd *new)
{
	t_cmd *str;

	if (*head == NULL)
	{
		*head = new;
		new->next = NULL;
	}
	else
	{
		str = *head;
		while (str->next != NULL)
			str = str->next;
		str->next = new;
		while (new && new->next != NULL)
		{
			str = str->next;
			str->next = new->next;
			new = new->next;
		}
		if (new)
			new->next = NULL;
	}
}

void	ft_link(char *ptr)
{
	t_var.skip_slash = 0;
	g_hnew = ft_lstnew_cmd(ft_strdup(ptr), check(ptr));
	ft_lstadd_back_cmd(&g_hcmd, g_hnew);
}

void	ft_lstadd_back(t_nod **head, t_nod *new)
{
	t_nod *str;

	if (*head == NULL)
	{
		*head = new;
		new->next = NULL;
	}
	else
	{
		str = *head;
		while (str->next != NULL)
			str = str->next;
		str->next = new;
		new->next = NULL;
	}
}
