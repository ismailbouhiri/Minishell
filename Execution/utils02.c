/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhiri <ibouhiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 20:00:40 by mlasrite          #+#    #+#             */
/*   Updated: 2020/12/11 19:02:14 by ibouhiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swap_data(struct s_srt *a, struct s_srt *b)
{
	char	*temp;
	char	*tmp;

	temp = a->key;
	a->key = b->key;
	b->key = temp;
	tmp = a->value;
	a->value = b->value;
	b->value = tmp;
}

void	ft_print_shead(void)
{
	t_sorted *tmp;

	tmp = g_shead;
	while (tmp)
	{
		write(1, "declare -x ", 11);
		write(1, tmp->key, ft_strlen(tmp->key));
		write(1, "=\"", 2);
		write(1, tmp->value, ft_strlen(tmp->value));
		write(1, "\"\n", 2);
		tmp = tmp->next;
	}
}

void	launch_it(char *path, t_cmd *cmd, char **env)
{
	int		len;
	char	**args;
	int		i;

	len = ft_lstsize(cmd);
	args = malloc(sizeof(char *) * (len + 1));
	args[len] = NULL;
	i = -1;
	while (i < len && cmd && cmd->what != POINT_VIRGULE && cmd->what != PIPE)
	{
		if (cmd->what == COMMAND || cmd->what == STRING)
			args[++i] = ft_strdup(cmd->cmd);
		cmd = cmd->next;
	}
	launch_it2(path, args, env);
}

void	launch_it2(char *path, char **args, char **env)
{
	pid_t	pid;
	int		i;

	g_stillexec = 1;
	pid = fork();
	if (pid < 0)
		exit(1);
	else if (pid == 0)
	{
		dup_it_pipe();
		dup_it();
		execve(path, args, env);
	}
	wait(&t_pipe.reti);
	i = 0;
	while (args[i] != NULL)
		free(args[i++]);
	free(args);
	g_stillexec = 0;
	if (g_ctrl_c == 1)
	{
		if (WIFSIGNALED(t_pipe.reti))
			write(1, "\n", 1);
	}
	t_pipe.reti = WEXITSTATUS(t_pipe.reti);
}

int		ft_check_equal(char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i);
		i += 1;
	}
	return (1);
}
