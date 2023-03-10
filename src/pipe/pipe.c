/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mich <mich@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:06:58 by mich              #+#    #+#             */
/*   Updated: 2023/02/16 11:50:15 by mich             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	change_in(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (shell->lst.input[++i])
		shell->lst.input[i] = ' ';
	i = 0;
	j = -1;
	while (shell->lst.pipe[1][++j])
	{
		shell->lst.input[i] = shell->lst.pipe[1][j];
		i++;
	}
	shell->lst.input[i] = '\0';
	executor(shell);
}

// int	ft_pipe(char **pip, t_shell *shell)
// {
// 	int	fd[2];
// 	int	status;
// 	int	pid;
// 	int	pid1;
// 	int	i;
// 	int k;

// 	(void)pip;
// 	i = -1;
// 	k = ft_count_arraystr(pip);
// 	i = dup(STDOUT_FILENO);
// 	// j = dup(STDIN_FILENO);
// 	if (pipe(fd) == -1)
// 		exit(printf("Failure\n"));
// 	pid = fork();
// 	//primo processo figlio
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[1]);
// 		// change_in(shell);
// 		printf("bho\n");
// 		if (k > 2)
// 			fork
// 		exit(EXIT_FAILURE);
// 	}
// 	//ritorno al processo padre
// 	else
// 	{
// 		dup2(i, STDOUT_FILENO);
// 		pid1 = fork();
// 		//crea un altro processo figlio
// 		if (pid1 == 0)
// 		{
// 			close(fd[1]);
// 			dup2(fd[0], STDIN_FILENO);
// 			close(fd[0]);
// 			change_in(shell);
// 			exit(EXIT_FAILURE);
// 		}
// 		//Ritorno al processo padre
// 		else
// 		{
// 			close(fd[0]);
// 			close(fd[1]);
// 			waitpid(pid, &status, 0);
// 			if (WIFEXITED(status))
// 				printf("fiuto\n");
// 			waitpid(pid1, &status, 0);
// 			if (WIFEXITED(status))
// 				printf("pippo\n");
// 		}
// 	}
// 	return (0);
// }

int	control_pipe(t_shell *shell)
{
	int	i;
	int	j;
	int	c;

	i = -1;
	j = 0;
	c = 0;
	while (shell->lst.input[++i])
	{
		if (is_pipe(shell->lst.input[i]) == 1)
		{
			j = 1;
			c++;
		}
	}
	if (j == 1)
	{
		shell->lst.pipe = split_pipe(shell->lst.input);
		// if (c == 1)
		// 	ft_pipe(shell->lst.pipe, shell);
		// else
		// 	cazzi_e_mazzi(shell->lst.pipe, shell);
	}
	return (0);
}
