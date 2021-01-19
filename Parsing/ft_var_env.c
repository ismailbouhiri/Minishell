/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhiri <ibouhiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 12:02:12 by ibouhiri          #+#    #+#             */
/*   Updated: 2020/12/10 10:06:25 by ibouhiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_collecte_env(char **env)
{
	char	ptr[5024];
	int		i;
	int		k;

	i = 0;
	while (env[i])
	{
		k = -1;
		while (env[i][++k] && env[i][k] != '=')
			ptr[k] = env[i][k];
		ptr[k] = '\0';
		g_new = ft_lstnew(ft_strdup(ptr), ft_strdup(env[i] + (k + 1)));
		ft_lstadd_back(&g_head, g_new);
		i++;
	}
}

void	ft_print_nod(void)
{
	t_nod	*tmp;

	tmp = g_head;
	dup_it_pipe();
	dup_it();
	if (path_exist())
	{
		while (tmp)
		{
			write(1, tmp->key, ft_strlen(tmp->key));
			write(1, "=", 1);
			write(1, tmp->value, ft_strlen(tmp->value));
			write(1, "\n", 1);
			tmp = tmp->next;
		}
	}
	else
		write(1, "No such file or directory\n", 26);
}

void	ft_add_env(char *line)
{
	t_nod	*test;
	int		k;
	char	tab[5024];

	k = -1;
	while (line[++k] && line[k] != '=')
		tab[k] = line[k];
	tab[k] = '\0';
	if (k == (int)ft_strlen(line))
		return ;
	test = g_head;
	while (test)
	{
		if (!(ft_strcmp(tab, test->key)))
		{
			free(test->value);
			test->value = ft_strdup(line + (k + 1));
			return ;
		}
		test = test->next;
	}
	g_new = ft_lstnew(ft_strdup(tab), ft_strdup(line + (k + 1)));
	ft_lstadd_back(&g_head, g_new);
}

void	ft_delete_nod(char *key)
{
	t_nod	*str;
	t_nod	*save;

	str = g_head;
	while (str)
	{
		save = str->next;
		if (str->next != NULL && !(ft_strcmp(key, save->key)))
		{
			str->next = save->next;
			free(save->key);
			free(save->value);
			free(save);
			return ;
		}
		if (!(ft_strcmp(key, str->key)))
		{
			free(str->key);
			free(str->value);
			free(str);
			g_head = save;
			return ;
		}
		str = str->next;
	}
}

char	*ft_find_value_env(char *key)
{
	t_nod	*tmp;

	tmp = g_head;
	while (tmp)
	{
		if (!(ft_strcmp(key, tmp->key)))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
