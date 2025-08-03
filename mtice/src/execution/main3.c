/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:31:26 by mtice             #+#    #+#             */
/*   Updated: 2025/07/12 13:59:36 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (argc < 5)
		return (ft_putstr_fd("Invalid arguments!\n", 2), 1);
	if (pipe(fd) == -1)
	 	return (2);
	pid1 = fork();
	if (pid1 < 0)
		return (3);
	if (pid1 == 0)
		child1(fd, argv, envp);
	pid2 = fork();
	if (pid2 < 0)
		return (4);
	if (pid2 == 0)
		child2(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
