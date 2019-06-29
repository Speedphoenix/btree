#include "node.h"

void		rb_check_edges(t_rb_tree *cont, t_rb_node *what)
{
	if (cont->begin == &g_leaf || cont->end == &g_leaf)
	{
		cont->begin = what;
		cont->end = what;
		return;
	}
	if (cont->compare(what->key, cont->begin->key))
		cont->begin = what;
	if (cont->compare(cont->end->key, what->key))
		cont->end = what;
}

void		rb_add_child(t_rb_tree *cont, t_rb_node *what, t_rb_node *parent,
				enum e_rb_direction dir)
{
	if (rb_tree_is_empty(cont))
		cont->root = what;
	else if (parent == &g_leaf || parent->children[dir] != &g_leaf)
		return;
	else
	{
		parent->children[dir] = what;
		what->parent = parent;
		what->dir_from_parent = dir;
	}
	rb_check_edges(cont, what);
	cont->nb_elements++;
}

t_rb_node	*rb_stupid_insert(t_rb_tree *container, t_rb_node *what)
{
	enum e_rb_direction	dir;
	t_rb_node			*parent;

	parent = rb_find_node(container, what->key);
	if (parent == &g_leaf || container->root == &g_leaf)
		rb_add_child(container, what, parent, 0);
	else
	{
		if (container->compare(parent->key, what->key))
			dir = RB_RIGHT;
		else if (container->compare(what->key, parent->key))
			dir = RB_LEFT;
		else
			return (NULL);
		rb_add_child(container, what, parent, dir);
	}
	what->children[RB_RIGHT] = &g_leaf;
	what->children[RB_LEFT] = &g_leaf;
	return (what);
}
