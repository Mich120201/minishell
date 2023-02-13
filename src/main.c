/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mich <mich@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:15:53 by mvolpi            #+#    #+#             */
/*   Updated: 2023/02/09 17:43:09 by mich             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src.h"

void	set_null(t_shell *shell)
{
	shell->lst.split = NULL;
	shell->lst.error = NULL;
	shell->lst.executor = NULL;
	shell->lst.expansion = NULL;
	shell->lst.file = NULL;
	shell->lst.pipe = NULL;
	shell->lst.redirection = NULL;
	shell->lst.input = NULL;
	shell->lst.doc = NULL;
	shell->lst.split = NULL;
	shell->lst.error = NULL;
	shell->lst.executor = NULL;
	shell->lst.expansion = NULL;
	shell->lst.file = NULL;
	shell->lst.pipe = NULL;
	shell->lst.redirection = NULL;
	shell->lst.input = NULL;
	shell->lst.doc = NULL;
	shell->env.current = NULL;
	shell->exp.sort_env = NULL;
	shell->cd.oldpwd = NULL;
	shell->cd.pwd2 = NULL;
	shell->cd.pwd = NULL;
}

void	free_str(char **str)
{
	int i;
	i = -1;
	while(str[++i])
	{
		free(str[i]);
		str[i] = NULL;
	}
	free(str);
}

void	free_struct2(t_shell *shell)
{
	if (shell->env.current)
		free_str(shell->env.current);
	shell->env.current = NULL;
	if (shell->exp.sort_env)
		free_str(shell->exp.sort_env);
	shell->exp.sort_env = NULL;
	if (shell->cd.oldpwd)
		free(shell->cd.oldpwd);
	shell->cd.oldpwd = NULL;
	if (shell->cd.pwd2)
		free(shell->cd.pwd2);
	shell->cd.pwd2 = NULL;
	if (shell->cd.pwd)
		free(shell->cd.pwd);
	shell->cd.pwd = NULL;
}

/**
 * @brief function that takes the structure of structures to be freed,
 * iterates cell by cell to be free and then does a general free of the
 * array
 * 
 * @param shell the structure of structures
 */
void	free_struct(t_shell *shell)
{
	if(shell->lst.split)
		free_str(shell->lst.split);
	shell->lst.split = NULL;
	if(shell->lst.error)
		free_str(shell->lst.error);
	shell->lst.error = NULL;
	if(shell->lst.executor)
		free_str(shell->lst.executor);
	shell->lst.executor = NULL;
	if (shell->lst.expansion)
		free_str(shell->lst.expansion);
	shell->lst.expansion = NULL;
	if (shell->lst.file)
		free_str(shell->lst.file);
	shell->lst.file = NULL;
	if (shell->lst.pipe)
		free_str(shell->lst.pipe);
	shell->lst.pipe = NULL;
	if (shell->lst.redirection)
		free_str(shell->lst.redirection);
	shell->lst.redirection = NULL;
	free(shell->lst.input);
	shell->lst.input = NULL;
	if (shell->lst.doc)
		free(shell->lst.doc);
	shell->lst.doc = NULL;
}

int	check_error_cod(t_shell *shell)
{
	int	i;

	i = -1;
	shell->lst.error = ft_split(shell->lst.input, ' ');
	while (shell->lst.error[++i])
	{
		if (ft_strncmp(shell->lst.error[i], "$?", 3) == 0)
		{
			printf("%d: command not found\n", g_exit);
			g_exit = parse(shell->lst.split);
			return (g_exit);
		}
		else
		{
			g_exit = 0;
			g_exit = parse(shell->lst.split);
		}
	}
	return (g_exit);
}

/**
 * @brief the start of the program that checks for errors,
 * saves the enviroment in a list and sets up a new prompt
 * waiting for a command and for now if in input there is
 * exit the program exit with no errors
 * 
 * @param argc number of argument in input from the teminal with which
 * we check that to start the programm only ./minishell is given in input
 * @param argv counter of argument in input from the terminal that
 * we set up at void because it is not needed within the program but
 * we need to call the force to have envp
 * @param envp an array where we have all the enviroment variables and we
 * need to save in a list where we can modify each variable to our liking
 * @return int return a 0 for now
 */
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	int		i;

	(void)argv;
	g_exit = 0;
	set_null(&shell);
	if (argc > 1)
		exit(printf("Error, there are too many argument!!"));
	get_env(envp, &shell);
	i = dup(STDOUT_FILENO);
	while (1)
	{
		shell.lst.input = readline("minishell: ");
		shell.lst.split = split_cmd(shell.lst.input);
		if (ft_strncmp(shell.lst.input, "", 1))
			add_history(shell.lst.input);
		g_exit = check_error_cod(&shell);
		if (g_exit == 0)
			check_operator(&shell);
		dup2(i, STDOUT_FILENO);
	}
	return (0);
}
