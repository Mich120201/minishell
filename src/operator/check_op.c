/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mich <mich@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:17:48 by mich              #+#    #+#             */
/*   Updated: 2023/02/20 11:54:53 by mich             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operator.h"

void	redirection(int c, t_shell *shell)
{
	shell->lst.redirection = split_redirection(shell->lst.input);
	shell->lst.file = ft_split(shell->lst.redirection[1], ' ');
	if (c == 1)
		red_out(shell->lst.file[0]);
	else if (c == 2)
		red_inp(shell->lst.file[0]);
	else if (c == 3)
		append(shell->lst.file[0]);
	else if (c == 4)
		here_doc(shell->lst.file[0], shell);
	delete_op(shell);
	executor(shell);
}

void	list_expansion(char *current, int pos, t_shell *shell)
{
	int i;
	char *str;

	i = -1;
	str = ft_strdup(current + pos);
	while (shell->lst.executor[++i])
	{
		if (ft_strncmp(shell->lst.executor[i], "$", 1) == 0)
			break;
	}
	free(shell->lst.executor[i]);
	shell->lst.executor[i] = ft_strdup(str + 1);
	free(str);
	str = NULL;
}	

int	check_red(char *input, t_shell *shell, int i)
{
	int	c;

	i = -1;
	c = 0;
	while (input[++i])
	{
		if (input[i] == '<' && input[i + 1] == '<')
		{
			c = 4;
			break ;
		}
		else if (input[i] == '>' && input[i + 1] == '>')
		{
			c = 3;
			break ;
		}
		else if (input[i] == '<')
			c = 2;
		else if (input[i] == '>')
			c = 1;
	}
	if (c > 0)
		redirection(c, shell);
	return(c);
}

void	expansion(t_shell *shell)
{
	int		i;
	int		pos;
	char	*str;

	i = -1;
	while (shell->lst.executor[++i])
	{
		if (ft_strncmp(shell->lst.executor[i], "$", 1) == 0)
			break;
	}
	str = ft_strdup(shell->lst.executor[i] + 1);
	i = -1;
	while (shell->env.current[++i])
	{		
		pos = ft_strchrp(shell->env.current[i], '=');
		if (ft_strncmp(shell->env.current[i], str, pos) == 0)
			list_expansion(shell->env.current[i], pos, shell);
	}
}

int	check_operator(t_shell *shell)
{
	int	i;
	int	q;

	i = -1;
	q = -1;
	q = clean_quote(shell, i);
	if (q == 0 || q == 3)
		executor(shell);
	else if (q == 1 || q == 4 || q == -1)
	{
		if (!control_pipe(shell))
			check_red(shell->lst.input, shell, i);
		executor(shell);
	}
	return (0);
}
