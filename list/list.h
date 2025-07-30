/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 09:11:15 by hfandres          #+#    #+#             */
/*   Updated: 2025/07/30 09:37:53 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H
# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	char			data;
	struct s_node	*next;
}	t_node;

typedef struct s_list
{
	t_node	*head;
	t_node	*tail;
	void	*data;
}	t_list;

t_list	*list_init(void);
int		list_is_empty(const t_list *list);
int		push_back(t_list *list, char data);
void	list_free(t_list *list);
void	list_print(const t_list *list);

#endif