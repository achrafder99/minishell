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

char* display_name(void) {
	char* username = getenv("USER");
	if (username == NULL) {
		write(2, "Could not get username", strlen("Could not get username"));
		return NULL;
	}
	char* display;
	display = ft_strjoin(username,"@:> ");
	return display;
	free(display); 
}

char* get_input(void) {
	char* full_username = display_name();
	if (full_username == NULL) {
		return NULL;
	}
	char* input = readline(full_username);
	free(full_username);
	return input;
}

void process_input(char* input, t_env* env, t_info* info) {
	if (input == NULL) {
		write(1, " exit\n", 6);
		exit(0);
	}
	if (strlen(input) == 0) {
		return;
	}
	add_history(input);
	t_components* head = NULL;
	lexer(input, &head, info, env);
}

int main(int argc, char** argv, char** envp) {
	char* input;
	char** spliting;
	char* clear_input;
	t_env* env;
	t_info* info;

	signal(SIGINT, interrupt_handler);
	signal(SIGQUIT, interrupt_handler);
	env = creat_env();
	env->env = get_env(envp);
	env->exp = get_export_env(envp);
	env->env_arr = NULL;
	rl_catch_signals = 0;

	while (1) {
		info = malloc(sizeof(t_info));
		if (!info) {
			perror("");
			exit(1);
		}
		input = get_input();
		if (input == NULL) {
			printf("exit\n");
			exit(1);
		}
		if (strrchr(input, ';')) {
			int i = 0;
			spliting = ft_split(input, ';');
			while (spliting[i]) {
				clear_input = restring(spliting[i], number(input));
				process_input(clear_input, env, info);
				free(clear_input);
				i++;
			}
		}
		else {
			clear_input = restring(input, number(input));
			process_input(clear_input, env, info);
			free(clear_input);
		}
		free(input);
		free(info);
	}
	free(env);
	return 0;
}