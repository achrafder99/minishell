/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:00:46 by aalami            #+#    #+#             */
/*   Updated: 2023/05/11 17:28:18 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

typedef struct s_here_node
{
	char				*data;
	struct s_here_node		*next;
}						t_here_node;

typedef struct s_here_data
{
	t_here_node				*top;
}						t_here_data;
#endif