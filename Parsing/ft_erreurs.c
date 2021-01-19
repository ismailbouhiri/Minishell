/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_erreurs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhiri <ibouhiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:38:36 by ibouhiri          #+#    #+#             */
/*   Updated: 2020/12/13 14:25:25 by ibouhiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	err_dec(void)
{
	write(1, "syntax error\n", 13);
	if (g_hcmd)
		free_lst();
	g_erreur = 1;
}

void	ft_command_var(t_cmd *findcmd, t_cmd **firstcmd, t_cmd **firstredir)
{
	if (findcmd->what == 5 || findcmd->what == 4 || findcmd->what == 6)
		t_var.directions++;
	if (findcmd->what == 2 || findcmd->what == 1)
		t_var.command++;
	*firstcmd = (t_var.command == 1 && !(*firstcmd)) ? findcmd : *firstcmd;
	*firstredir = (t_var.directions == 1 && !(*firstredir))
	? findcmd : *firstredir;
}

char	*ft_strcpy(char *dest, const char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	if (!s1 || !s2)
		return (s1[i] - s2[i]);
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
