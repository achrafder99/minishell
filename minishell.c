/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:52:42 by adardour          #+#    #+#             */
/*   Updated: 2023/05/08 18:08:00 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	interrupt_handler(int signal)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
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

	input = NULL;
	full_username = display_name();
	tt = ft_strjoin(full_username, "");
	input = readline(tt);
	free(full_username);
	free(tt);
	return (input);
}

void	process_input(char *input, t_env *env)
{
	t_components	*head;
	t_info			*info;

	info = malloc(sizeof(t_info));
	if (!info)
		exit(1);
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
	printf("Status Exit %d\n",info->status_code);
	head = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*clear_input;
	t_env	*env;

	signal(SIGINT, interrupt_handler);
	env = creat_env();
	env->env = get_env(envp);
	env->exp = get_export_env(envp);
	env->env_arr = NULL;
	rl_catch_signals = 0;
	while (1)
	{
		input = get_input();
		if (input == NULL)
		{
			printf("exit\n");
			exit(1);
		}
		clear_input = restring(input, number(input));
		process_input(clear_input, env);
	}
}
