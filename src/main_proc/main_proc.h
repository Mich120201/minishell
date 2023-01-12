/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_proc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbellucc <vbellucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:22:42 by mvolpi            #+#    #+#             */
/*   Updated: 2023/01/11 11:13:34 by vbellucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_PROC_H
# define MAIN_PROC_H

# include "../../h_file/minishell.h"

/*init_env.c*/
void	get_env(char **envp, t_shell *env_list);
/*split_in*/
int		is_separator(char c);
int		words(char *str);
void	write_word(char *dest, char *src);
int		write_split(char **split, char *str);
char	**split_cmd(char const *s);

#endif
