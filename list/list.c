/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandres <hfandres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 09:18:36 by hfandres          #+#    #+#             */
/*   Updated: 2025/07/29 10:47:54 by hfandres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*list_init(void)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->head = NULL;
	list->tail = NULL;
	list->data = NULL;
	return (list);
}

int	list_is_empty(const t_list *list)
{
	return (list->head == NULL);
}

int	push_back(t_list *list, char data)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (0);
	new_node->data = data;
	new_node->next = NULL;
	if (list_is_empty(list))
	{
		list->head = new_node;
		list->tail = new_node;
	}
	else
	{
		list->tail->next = new_node;
		list->tail = new_node;
	}
	return (1);
}

void	list_free(t_list *list)
{
	t_node	*current;
	t_node	*next_node;

	current = list->head;
	while (current)
	{
		next_node = current->next;
		free(current);
		current = next_node;
	}
	list->head = NULL;
	list->tail = NULL;
	list->data = NULL;
}

void	list_print(const t_list *list)
{
	t_node	*current;

	current = list->head;
	while (current)
	{
		write(1, &current->data, 1);
		current = current->next;
	}
	write(1, "\n", 1);
}
