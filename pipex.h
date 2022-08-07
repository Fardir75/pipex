/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavilov <eavilov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:37:54 by eavilov           #+#    #+#             */
/*   Updated: 2022/04/13 14:45:23 by eavilov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*  🐄 pouin-ach 🐄 	*/

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include "libft/libft.h"

/*	---- 🐄 Strcgfrutretures 🐄 ---- */

typedef struct s_pipex {
	char	**argv;
	char	**envpath;
	char	**envp;
	char	*execpath1;
	char	*execpath2;
	char	**cmd1;
	char	**cmd2;
	int		cmdpath1;
	int		cmdpath2;
	int		argc;
	int		i;
}			t_pipex;

/*	---- 🐄 Functions 🐄 ---- */

char	**ft_slashadd(t_pipex *vars);

int		ft_find_index(const char *s, int c);

void	ft_initiate(t_pipex *vars, char **av, int ac, char **env);
void	ft_child1(t_pipex *vars, int fd[2], int f1);
void	ft_child2(t_pipex *vars, int fd[2], int f2);
void	ft_check_error(t_pipex *vars, int c);
void	ft_pathparser(t_pipex *vars);
void	ft_find_path(t_pipex *vars);
void	ft_cmd_check(t_pipex *vars);
void	ft_free_all(t_pipex *vars);
void	ft_pipex(t_pipex *vars);
void	func_exit(char *s);
void	ft_double_close(int fd[2]);

#endif