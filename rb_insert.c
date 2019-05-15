#include "btree.h"
#include "node.h"
#include "stdlib.h"

/*
**	Returns true (1) on success, false (0) on failure
**	Failure can be if malloc returns NULL or if the key exists already
*/
int		rb_insert(t_rb_tree *tree, t_key key, t_data data)
{
	t_rb_node	*new_elem;

	new_elem = rb_create_node(key, data);
	if (rb_stupid_insert(tree, new_elem) != new_elem)
	{
		free(new_elem);
		return (0);
	}
	rb_correct_insert(new_elem);
	while (new_elem->parent != &g_leaf)
		new_elem = new_elem->parent;
	tree->root = new_elem;
	return (1);
}

void	rb_correct_insert(t_rb_node *new_elem)
{
	if (new_elem->parent == &g_leaf)
	{
		new_elem->color = RB_BLACK;
		return;
	}
	else if (new_elem->parent->color == RB_BLACK)
	{
		return;
	}
	else if (rb_get_uncle(new_elem)->color == RB_RED)
	{
		new_elem->parent->color = RB_BLACK;
		rb_get_uncle(new_elem)->color = RB_BLACK;
		rb_get_grandp(new_elem)->color = RB_RED;
		rb_correct_insert(rb_get_grandp(new_elem));
	}
	else
		rb_insert_last_case(new_elem);
}

void	rb_insert_last_case(t_rb_node *new_el)
{
	t_rb_node *parent;
	t_rb_node *gparent;

	if (new_el->dir_from_parent != new_el->parent->dir_from_parent)
	{
		rb_rotate(new_el->parent, new_el->parent->dir_from_parent);
		parent = new_el;
	}
	else
		parent = new_el->parent;
	gparent = parent->parent;
	rb_rotate(gparent, !parent->dir_from_parent);
	parent->color = RB_BLACK;
	gparent->color = RB_RED;
}
