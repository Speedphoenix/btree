#include "btree.h"
#include "node.h"
#include <stdlib.h>

void		rb_init_tree(t_rb_tree *what, t_compare_func compare)
{
	what->root = &g_leaf;
	what->begin = &g_leaf;
	what->end = &g_leaf;
	what->compare = compare;
	what->nb_elements = 0;
}

t_rb_tree	*rb_create_tree(t_compare_func compare)
{
	t_rb_tree	*rep;

	rep = (t_rb_tree*)malloc(sizeof(t_rb_tree));
	if (rep)
	{
		rb_init_tree(rep, compare);
	}
	return (rep);
}

void		rb_reset_edge(t_rb_tree *tree, enum e_rb_direction dir)
{
	t_rb_node	*curr;

	if (tree->root == &g_leaf)
	{
		tree->begin = &g_leaf;
		tree->end = &g_leaf;
		return;
	}
	curr = tree->root;
	while (curr->children[dir] != &g_leaf)
		curr = curr->children[dir];
	if (dir == RB_LEFT)
		tree->begin = curr;
	else
		tree->end = curr;
}
