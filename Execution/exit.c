/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 12:39:24 by mlasrite          #+#    #+#             */
/*   Updated: 2020/12/10 12:14:52 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_entry(t_cmd *tmp)
{
	int retvalue;

	if ((tmp && tmp->next && tmp->next->what != STRING) || (tmp && !tmp->next))
		simple_exit();
	else if (tmp && tmp->next && is_digit(tmp->next->cmd))
	{
		if (tmp && (tmp->next && tmp->next->what == STRING)
		&& (tmp->next->next && tmp->next->next->what == STRING))
			ft_norminetteexit();
		else
		{
			if (beforepipe(t_pipe.k) != 1 && check_pipe(t_pipe.k) != 1)
			{
				retvalue = ft_atoi(tmp->next->cmd);
				free_nod();
				free_lst();
				free(t_main.line);
				t_main.line = NULL;
				write(1, "exit\n", 5);
				exit(retvalue);
			}
		}
	}
	else
		num_required_exit(tmp);
}

int		is_digit(char *str)
{
	int i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	return (1);
}

int		ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - 48);
		if (res > 2147483648 && sign == -1)
			return (0);
		if (res > 2147483647 && sign == 1)
			return (-1);
		i++;
	}
	return (res * sign);
}

void	num_required_exit(t_cmd *tmp)
{
	if (beforepipe(t_pipe.k) != 1 && check_pipe(t_pipe.k) != 1)
	{
		free_nod();
		free_lst();
		free(t_main.line);
		t_main.line = NULL;
		write(1, "exit\n", 5);
		write(1, "exit: ", 6);
		write(1, tmp->next->cmd, ft_strlen(tmp->next->cmd));
		write(1, ": numeric argument required\n", 28);
		exit(0);
	}
	else
	{
		write(1, "exit: ", 6);
		write(1, tmp->next->cmd, ft_strlen(tmp->next->cmd));
		write(1, ": numeric argument required\n", 28);
	}
}

void	simple_exit(void)
{
	if (beforepipe(t_pipe.k) != 1 && check_pipe(t_pipe.k) != 1)
	{
		free_nod();
		free_lst();
		free(t_main.line);
		t_main.line = NULL;
		write(1, "exit\n", 5);
		exit(0);
	}
}
