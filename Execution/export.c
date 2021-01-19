/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhiri <ibouhiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 02:23:57 by mlasrite          #+#    #+#             */
/*   Updated: 2020/12/11 12:28:26 by ibouhiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export(t_cmd *tmp)
{
	tmp = tmp->next;
	if (tmp == NULL || (tmp && tmp->what != STRING))
	{
		copy_list();
		ft_print_shead();
		free_shead();
	}
	else
	{
		while (tmp && tmp->what == STRING)
		{
			if (!ft_check_equal(tmp->cmd) || ft_check_key(tmp->cmd))
				write(1, "not a valid identifier\n", 23);
			else if (ft_check_equal(tmp->cmd))
				ft_add_env(tmp->cmd);
			tmp = tmp->next;
		}
	}
}

void	copy_list(void)
{
	t_nod	*tmp;
	int		i;

	i = 0;
	tmp = g_head;
	while (tmp)
	{
		fill(tmp->key, tmp->value);
		tmp = tmp->next;
	}
	sort_shead();
}

void	fill(char *key, char *value)
{
	t_sorted *ptr1;

	ptr1 = (t_sorted *)malloc(sizeof(t_sorted));
	ptr1->key = ft_strdup(key);
	ptr1->value = ft_strdup(value);
	ptr1->next = NULL;
	add_back(ptr1);
}

void	sort_shead(void)
{
	t_sorted	*tmp;
	t_sorted	*n;
	int			acce;

	acce = 1;
	while (acce)
	{
		tmp = g_shead;
		acce = 0;
		while (tmp)
		{
			n = tmp->next;
			if (n != NULL)
			{
				acce = help_sort_shead(tmp, n, acce);
			}
			tmp = tmp->next;
		}
	}
}

int		help_sort_shead(t_sorted *tmp, t_sorted *n, int acce)
{
	int i;
	int a;

	i = 0;
	a = 0;
	while (a != 1337)
	{
		if (tmp->key[i] > n->key[i])
		{
			swap_data(tmp, n);
			acce = 1;
			a = 1337;
		}
		else if (tmp->key[i] < n->key[i])
			a = 1337;
		else
			i += 1;
	}
	return (acce);
}
