/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 22:47:25 by adardour          #+#    #+#             */
/*   Updated: 2023/05/23 15:58:33 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_environment(t_env **env, t_info **info, char **envp)
{
	signal(SIGINT, interrupt_handler);
	signal(SIGQUIT, interrupt_handler);
	*env = creat_env();
	(*env)->env = get_env(envp);
	(*env)->exp = get_export_env(envp);
	(*env)->env_arr = NULL;
	rl_catch_signals = 0;
	*info = malloc(sizeof(t_info));
	if (!(*info))
	{
		perror("");
		exit(1);
	}
	(*info)->status_code = 0;
}

void	start_proccesing(char *input, t_info *info, t_env *env)
{
	char	**splitting;
	int		i;

	if (input == NULL)
		return (printf("exit\n"), exit(0));
	if (ft_strchr(input, ';'))
	{
		i = 0;
		splitting = ft_split(input, ';');
		while (splitting[i])
		{
			process_input(input, env, info);
			i++;
		}
	}
	else
		process_input(input, env, info);
}

void	process_input_loop(t_env *env, t_info *info)
{
	char	*input;

	while (1)
	{
		input = get_input();
		start_proccesing(input, info, env);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_info	*info;
	t_env	*env;

	(void)argc;
	(void)argv;
	initialize_environment(&env, &info, envp);
	process_input_loop(env, info);
	free(info);
	return (0);
}
