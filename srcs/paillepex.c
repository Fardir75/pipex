/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paillepex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavilov <eavilov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 07:46:54 by eavilov           #+#    #+#             */
/*   Updated: 2022/04/15 08:57:56 by eavilov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_child1(t_pipex *vars, int fd[2], int f1)
{
	if (dup2(f1, STDIN_FILENO) == -1)
		func_exit("Error : Dup of infile failed\n");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		func_exit("Error : Pipe dup of child1 failed\n");
	close(f1);
	close(fd[0]);
	if (execve(vars->execpath1, vars->cmd1, vars->envp) == -1)
		func_exit("Error : First child execve failed\n");
	exit(0);
}

void	ft_child2(t_pipex *vars, int fd[2], int f2)
{
	if (dup2(f2, STDOUT_FILENO) == -1)
		func_exit("Error : Dup of outfile failed\n");
	if (dup2(fd[0], STDIN_FILENO) == -1)
		func_exit("Error : Pipe dup of child2 failed\n");
	close(f2);
	close(fd[1]);
	close(fd[0]);
	if (execve(vars->execpath2, vars->cmd2, vars->envp) == -1)
		func_exit("Error : Second child execve failed\n");
	exit(0);
}

void	ft_double_close(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	ft_pipex(t_pipex *vars)
{
	pid_t	fk[2];
	int		fopen[2];
	int		fd[2];

	if (pipe(fd) == -1)
		func_exit("Error : Pipe failed\n");
	fopen[0] = open(vars->argv[1], O_RDONLY);
	fopen[1] = open(vars->argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fopen[1] == -1)
		fopen[1] = open(vars->argv[4], O_CREAT | O_WRONLY, 0644);
	fk[0] = fork();
	if (fk[0] < 0)
		func_exit("Error : Fork Failed\n");
	if (fk[0] == 0)
		ft_child1(&*vars, fd, fopen[0]);
	fk[1] = fork();
	if (fk[1] < 0)
		func_exit("Error : Fork 2 Failed\n");
	if (fk[1] == 0)
		ft_child2(&*vars, fd, fopen[1]);
	ft_double_close(fd);
	if (waitpid(fk[0], 0, 0) == -1)
		func_exit("Error : Waitpid1 failed\n");
	if (waitpid(fk[1], 0, 0) == -1)
		func_exit("Error : Waitpid2 failed\n");
}
