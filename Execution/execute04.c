/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute04.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlasrite <mlasrite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 20:42:15 by mlasrite          #+#    #+#             */
/*   Updated: 2020/12/08 17:16:43 by mlasrite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	search_it(t_cmd *cmd, char **env)
{
	char		*path;
	int			fd;
	int			ret;

	path = NULL;
	fd = 0;
	ret = 0;
	if (cmd->cmd[0] == '/' || cmd->cmd[0] == '.')
		search_it2(path, cmd, fd, env);
	else
		search_it3(env, cmd, fd, path);
}

void	search_it3(char **env, t_cmd *cmd, int fd, char *path)
{
	t_nod		*tmp;
	char		**v_path;
	int			ret;

	tmp = g_head;
	v_path = NULL;
	ret = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
		{
			v_path = ft_split(tmp->value, ':');
			break ;
		}
		tmp = tmp->next;
	}
	if (v_path)
	{
		if ((ret = search_it4(v_path, cmd, fd, env)) == 1)
			return ;
		free_vpath(v_path);
		free(path);
	}
	write(1, "command not found\n", 18);
	t_pipe.reti = 127;
}

int		search_it4(char **v_path, t_cmd *cmd, int fd, char **env)
{
	int			i;
	char		*str;
	struct stat file;

	i = -1;
	while (v_path[++i])
	{
		str = ft_strjoin(v_path[i], "/");
		t_var.path = ft_strjoin(str, cmd->cmd);
		free(str);
		if ((fd = open(t_var.path, O_RDONLY)) > 0)
		{
			fstat(fd, &file);
			close(fd);
			if (file.st_mode & S_IXUSR)
				launch_it(t_var.path, cmd, env);
			else
				write(1, "Permission denied\n", 18);
			free_vpath(v_path);
			free(t_var.path);
			return (1);
		}
		free(t_var.path);
	}
	return (0);
}

void	search_it2(char *path, t_cmd *cmd, int fd, char **env)
{
	struct stat file;

	path = cmd->cmd;
	fd = open(path, O_RDONLY);
	if (fd > 0)
	{
		fstat(fd, &file);
		close(fd);
		if (file.st_mode & S_IXUSR)
			launch_it(path, cmd, env);
		else
			write(1, "Permission denied\n", 18);
	}
	else
	{
		write(1, "command not found\n", 18);
		t_pipe.reti = 127;
	}
}

void	free_vpath(char **v_path)
{
	int i;

	i = 0;
	while (v_path[i] != NULL)
		free(v_path[i++]);
	free(v_path);
}
