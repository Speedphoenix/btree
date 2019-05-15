#include "node.h"
#include <stdlib.h>

t_rb_node	g_leaf = {NULL, {NULL, NULL}, NULL, NULL, RB_BLACK, RB_LEFT};

void		rb_init_node(t_rb_node *what, t_key key, t_data data)
{
	what->parent = &g_leaf;
	what->children[RB_LEFT] = &g_leaf;
	what->children[RB_RIGHT] = &g_leaf;
	what->key = key;
	what->data = data;
	what->color = RB_RED;
	what->dir_from_parent = RB_LEFT;
}

t_rb_node	*rb_create_node(t_key key, t_data data)
{
	t_rb_node	*rep;

	rep = (t_rb_node*)malloc(sizeof(t_rb_node));
	if (rep)
	{
		rb_init_node(rep, key, data);
	}
	return (rep);
}

void		rb_swap_user_contents(t_rb_node *a, t_rb_node *b)
{
	t_key	kc;
	t_data	dc;

	kc = a->key;
	dc = a->data;
	a->key = b->key;
	a->data = b->data;
	b->key = kc;
	b->data = dc;
}
