/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavilov <eavilov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 07:44:07 by eavilov           #+#    #+#             */
/*   Updated: 2022/04/13 11:09:47 by eavilov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_find_index(const char *s, int c)
{
	int		i;

	i = -1;
	if (!s)
		return (-1);
	while (s[++i])
	{
		if (s[i] == c)
			return (i);
	}
	return (i);
}

char	**ft_slashadd(t_pipex *vars)
{
	int		i;
	int		count;
	char	**res;

	i = 0;
	count = 0;
	while (vars->envpath[count])
		count++;
	res = malloc(sizeof(char *) * (count + 1));
	while (vars->envpath[i])
	{
		res[i] = ft_strjoin(vars->envpath[i], "/");
		i++;
	}
	res[count] = NULL;
	ft_freesbee(vars->envpath);
	return (res);
}

void	ft_find_path(t_pipex *vars)
{
	int		i;
	char	*temp;

	i = -1;
	temp = NULL;
	while (vars->envpath[++i])
	{
		if (vars->cmdpath1 == 0)
		{
			temp = ft_strjoin(vars->envpath[i], vars->cmd1[0]);
			if (access(temp, F_OK) == 0)
				vars->execpath1 = ft_strjoin(vars->envpath[i], vars->cmd1[0]);
			free(temp);
		}
		if (vars->cmdpath2 == 0)
		{
			temp = ft_strjoin(vars->envpath[i], vars->cmd2[0]);
			if (access(temp, F_OK) == 0)
				vars->execpath2 = ft_strjoin(vars->envpath[i], vars->cmd2[0]);
			free(temp);
		}
	}
}

void	ft_pathparser(t_pipex *vars)
{
	int		i;
	char	*temp;

	i = -1;
	temp = NULL;
	if (vars->cmdpath1 == 0)
		vars->cmd1 = ft_split(vars->argv[2], ' ');
	if (vars->cmdpath2 == 0)
		vars->cmd2 = ft_split(vars->argv[3], ' ');
	if (vars->cmdpath1 > 0 && vars->cmdpath2 > 0)
		return ;
	while (vars->envp[++i])
	{
		if (ft_strncmp(vars->envp[i], "PATH=", 5) == 0)
			temp = ft_substr(vars->envp[i], 5, ft_strlen(vars->envp[i]));
	}
	if (!temp)
	{
		ft_putstr("Warning : PATH not found\n");
		return ;
	}
	vars->envpath = ft_split(temp, ':');
	vars->envpath = ft_slashadd(&*vars);
	free(temp);
	ft_find_path(&*vars);
}
