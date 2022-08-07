/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavilov <eavilov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 07:37:26 by eavilov           #+#    #+#             */
/*   Updated: 2022/04/15 07:56:23 by eavilov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_initiate(t_pipex *vars, char **av, int ac, char **env)
{
	vars->argv = av;
	vars->envp = env;
	vars->argc = ac;
	vars->cmdpath1 = 0;
	vars->cmdpath2 = 0;
	vars->execpath1 = NULL;
	vars->execpath2 = NULL;
	vars->envpath = NULL;
}

void	func_exit(char *s)
{
	ft_putstr(s);
	exit (0);
}

void	ft_check_error(t_pipex *vars, int c)
{
	if (c == 1)
	{
		if (vars->argc != 5)
			func_exit("Error : Incorrect amount of arguments\n");
		if (access(vars->argv[1], F_OK) == 0
			&& access(vars->argv[1], R_OK) != 0)
			ft_putstr("Warning : Permission to the infile denied\n");
		if (access(vars->argv[1], F_OK) != 0)
			ft_putstr("Warning : Can't access the infile\n");
		if (access(vars->argv[4], F_OK) == 0
			&& access(vars->argv[4], W_OK) != 0)
			ft_putstr("Warning : Write permission to the outfile denied\n");
		if (access(vars->argv[4], F_OK) == 0
			&& access(vars->argv[4], R_OK) != 0)
			ft_putstr("Warning : Read permission to the outfile denied\n");
	}
	else
	{
		if (access(vars->execpath1, F_OK) != 0)
			ft_putstr("Warning : Your first function doesn't work\n");
		if (access(vars->execpath2, F_OK) != 0)
			ft_putstr("Warning : Your second function doesn't work\n");
	}
}

char	*ft_split_grab(char	*s)
{
	int		i;
	char	*res;
	char	**cpy;

	i = 0;
	res = NULL;
	cpy = ft_split(s, ' ');
	res = ft_strdup(cpy[0]);
	ft_freesbee(cpy);
	return (res);
}

void	ft_cmd_check(t_pipex *vars)
{
	char	*path1;
	char	*path2;

	path1 = NULL;
	path2 = NULL;
	if (vars->argv[2][0] == '/')
		path1 = ft_substr(vars->argv[2], 0, ft_find_index(vars->argv[2], ' '));
	if (vars->argv[3][0] == '/')
		path2 = ft_substr(vars->argv[3], 0, ft_find_index(vars->argv[3], ' '));
	if (access(path1, F_OK) == 0)
	{
		vars->cmdpath1++;
		vars->cmd1 = ft_split(ft_my_strrchr(vars->argv[2], '/', -1), ' ');
		vars->execpath1 = ft_split_grab(vars->argv[2]);
	}
	if (access(path2, F_OK) == 0)
	{
		vars->cmdpath2++;
		vars->cmd2 = ft_split(ft_my_strrchr(vars->argv[3], '/', -1), ' ');
		vars->execpath2 = ft_split_grab(vars->argv[3]);
	}
	free(path1);
	free(path2);
}
