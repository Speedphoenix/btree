#include "btree.h"
#include "node.h"

int			rb_rotate(t_rb_node *root, enum e_rb_direction dir)
{
	t_rb_node	*pivot;
	t_rb_node	*problem_child;

	pivot = root->children[!dir];
	if (pivot == &g_leaf || root == &g_leaf)
		return (0);
	rb_set_new_parent(pivot, root->parent, root->dir_from_parent);
	problem_child = rb_set_new_parent(root, pivot, dir);
	rb_set_new_parent(problem_child, root, !dir);
	return (1);
}

/*
**	Returns the child that was kicked out of the parent
*/
t_rb_node	*rb_set_new_parent(t_rb_node *what, t_rb_node *parent,
				enum e_rb_direction dir)
{
	t_rb_node	*rep;

	if (parent != &g_leaf)
	{
		rep = parent->children[dir];
		parent->children[dir] = what;
	}
	else
		rep = &g_leaf;
	if (what != &g_leaf)
	{
		what->parent = parent;
		what->dir_from_parent = dir;
	}
	return (rep);
}

t_rb_node	*rb_get_grandp(t_rb_node *from)
{
	if (from == &g_leaf)
		return (&g_leaf);
	if (from->parent != &g_leaf && from->parent->parent != &g_leaf)
		return (from->parent->parent);
	return (&g_leaf);
}

t_rb_node	*rb_get_sibling(t_rb_node *from)
{
	if (from == &g_leaf)
		return (&g_leaf);
	if (from->parent == &g_leaf)
		return (&g_leaf);
	return (from->parent->children[!from->dir_from_parent]);
}

t_rb_node	*rb_get_uncle(t_rb_node *from)
{
	if (from == &g_leaf)
		return (&g_leaf);
	return (rb_get_sibling(from->parent));
}
