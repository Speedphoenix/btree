#include "ft_queue.h"
#include <stdlib.h>
#include "node.h"

void	push_queue(t_queue **front, t_queue **back, t_rb_node *data, int level)
{
	t_queue	*new_elem;

	new_elem = malloc(sizeof(*new_elem));
	new_elem->data = data;
	new_elem->level = level;
	new_elem->next = NULL;
	if (*back == NULL)
		*front = new_elem;
	else
		(*back)->next = new_elem;
	*back = new_elem;
}

void	pop_queue(t_queue **front, t_queue **back)
{
	t_queue	*to_remove;

	if (*front == NULL)
		return ;
	to_remove = *front;
	*front = to_remove->next;
	if (*back == to_remove)
		*back = NULL;
	free(to_remove);
}

void	btree_apply_by_level(t_rb_tree *tree,
			void (*applyf)(t_rb_node *item, int current_level,
				int is_first_elem))
{
	t_rb_node	*node;
	t_queue 	*q_front;
	t_queue 	*q_back;
	int			level;

	q_front = NULL;
	q_back = NULL;
	level = -1;
	push_queue(&q_front, &q_back, tree->root, 0);
	while (q_front != NULL)
	{
		node = q_front->data;
		applyf(node, q_front->level, (q_front->level != level));
		level = q_front->level;
		if (node->children[RB_LEFT] != &g_leaf)
			push_queue(&q_front, &q_back, node->children[RB_LEFT], level + 1);
		if (node->children[RB_RIGHT] != &g_leaf)
			push_queue(&q_front, &q_back, node->children[RB_RIGHT], level + 1);
		pop_queue(&q_front, &q_back);
	}
}
