/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:52:42 by adardour          #+#    #+#             */
/*   Updated: 2023/05/13 23:40:02 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	interrupt_handler(int signal)
{
	if (signal == 3)
		printf("");
	else
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

char	*display_name(void)
{
	char	*username;
	char	*full_username;
	char	*temp;
	char	*dd;

	username = ft_strjoin(getenv("USER"), "@:");
	temp = username;
	if (temp == NULL)
		write(2, "Could not get username", ft_strlen("Could not get username"));
	dd = ft_strjoin(temp, " > ");
	free(username);
	return (dd);
}

char	*get_input(void)
{
	char	*input;
	char	*full_username;
	char	*tt;

	full_username = display_name();
	tt = ft_strjoin(full_username, "");
	input = readline(tt);
	free(full_username);
	free(tt);
	return (input);
}

void	process_input(char *input, t_env *env, t_info *info)
{
	t_components	*head;

	head = malloc(sizeof(head));
	if (input == NULL)
	{
		write(1, " ", 1);
		write(1, "exit\n", 5);
		exit(0);
	}
	else if (strlen(input) == 0)
		return ;
	head = NULL;
	add_history(input);
	lexer(input, &head, info, env);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**spliting;
	char	*clear_input;
	t_env	*env;
	t_info 	*info;

	signal(SIGINT, interrupt_handler);
	signal(SIGQUIT, interrupt_handler);
	env = creat_env();
	env->env = get_env(envp);
	env->exp = get_export_env(envp);
	env->env_arr = NULL;
	rl_catch_signals = 0;
	while (1)
	{
		info = malloc(sizeof(t_info));
		if (!info)
			exit(1);
		input = get_input();
		if (input == NULL)
		{
			printf("exit\n");
			exit(1);
		}
		if (strrchr(input,';'))
		{
			int i = 0;
			spliting = ft_split(input,';');
			while (spliting[i])
			{
				clear_input = restring(spliting[i], number(input));
				process_input(clear_input, env, info);
				free(clear_input);
				i++;
			}
		}
		else
		{
			clear_input = restring(input, number(input));
			free(input);
			process_input(clear_input, env, info);
			free(clear_input);
			clear_input =  NULL;
		}
		free(info);
	}
}