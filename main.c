/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavilov <eavilov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 03:59:27 by eavilov           #+#    #+#             */
/*   Updated: 2022/08/07 11:58:41 by eavilov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_all(t_pipex *vars)
{
	ft_freesbee(vars->cmd1);
	ft_freesbee(vars->cmd2);
	free(vars->execpath1);
	free(vars->execpath2);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	vars;

	ft_initiate(&vars, av, ac, env);
	ft_check_error(&vars, 1);
	ft_cmd_check(&vars);
	ft_pathparser(&vars);
	ft_check_error(&vars, 2);
	ft_pipex(&vars);
	ft_free_all(&vars);
	return (0);
}
