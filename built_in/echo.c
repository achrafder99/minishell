/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:21:31 by adardour          #+#    #+#             */
/*   Updated: 2023/04/30 11:14:24 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_env(char *string,t_info *info)
{
	
	int i;
	while (*string != '\0' && *string != '$')
	{
		if(*string == '\\'){
			string++;
            if(*string == '\'')
                write(1, "\'", 1);
            else if(*string == '\"')
                write(1, "\"", 1);
            else if(*string == '$')
                write(1, "$", 1);
            else if(*string == ';')
                write(1, ";", 1);
            else if(*string == '|')
                write(1, "|", 1);
            else if(*string == '<')
                write(1, "<", 1);
            else if(*string == '>')
                write(1, ">", 1);
            else if(*string == '&')
                write(1, "&", 1);
			else
				write(1,string,1);
        }
		else
			write(1,string,1);
		string++;
	}
	char **spliting;
	char *value;
	spliting = ft_split(string,'$');
	i = 0;
	while (spliting[i] != NULL)
	{
		if(spliting[i][0] == '?')
		{
			printf("%d\n",info->status_code);
			int j;
			j = 1;
			while (spliting[i][j] != '\0')
			{
				write(1,&spliting[i][j],1);
				j++;
			}
		}
		value = getenv(spliting[i]);
		if (!value) 
			write(1,"",1);
		else
			write(1, value, ft_strlen(value));
		i++;
	}
}

void put(char *string){
		int i;
		i = 0;
		while(string[i] != '\0'){
			write(1,&string[i],1);
			i++;
		}
		write(1," ",1);
}

void ft_put_echo(char *string){    
    while(*string != '\0'){
        if(*string == '\\'){
            string++;
            if(*string == '\'')
                write(1, "\'", 1);
            else if(*string == '\"')
                write(1, "\"", 1);
            else if(*string == '$')
                write(1, "$", 1);
            else if(*string == ';')
                write(1, ";", 1);
            else if(*string == '|')
                write(1, "|", 1);
            else if(*string == '<')
                write(1, "<", 1);
            else if(*string == '>')
                write(1, ">", 1);
            else if(*string == '&')
                write(1, "&", 1);
            else
                write(1,string,1);
        }
        else
            write(1,string,1);
        string++;
    }
}

int	get_length(char **commands)
{
	int	i;

	i = 0;
	while (commands[i] != NULL)
		i++;
	return (i);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int echo(t_command *cmd,t_info *info)
{

    int i;
    int flags;
	i = 0;
	
	flags = 0;
    if (cmd->argc == 0)
	{
        write(1, "\n", 1);
        return (1);
    }
    while (cmd->args[i] != NULL && !ft_strcmp(cmd->args[i], "-n"))
	{
        flags = 1;
        i++;
    }
    while (cmd->args[i] != NULL)
	{
        if (ft_strchr(cmd->args[i],'$'))
		{
			print_env(cmd->args[i],info);
			write(1," ",1);
		}
		else
		{
			ft_put_echo(cmd->args[i]);
			// write(1," ",1);
		}
        i++;
    }
    if (!flags) 
        write(1, "\n", 1);
	return (0);
}