#include "node.h"

t_data				rb_remove(t_rb_tree *tree, t_key key)
{
	t_rb_node	*to_remove;
	t_data		rep;

	to_remove = rb_find_node(tree, key);
	if ((to_remove == &g_leaf)
		|| tree->compare(to_remove->key, key)
		|| tree->compare(key, to_remove->key))
		return (NULL);
	rep = to_remove->data;
	to_remove = rb_remove_node(tree, to_remove);
	if (!tree->compare(tree->begin->key, key))
		rb_reset_edge(tree, RB_LEFT);
	if (!tree->compare(key, tree->end->key))
		rb_reset_edge(tree, RB_RIGHT);
	rb_node_destroy(to_remove);
	tree->nb_elements--;
	return (rep);
}

/*
**	TODO: make the direction in which we take the innermost child
**	alternate/random
*/
enum e_rb_direction	rb_alternate_dir(void)
{
	static enum e_rb_direction	a = RB_LEFT;

	a = !a;
	return (a);
}

void				rb_rebalance_last_case_rem(t_rb_node *to_remove)
{
	t_rb_node	*sibling;

	sibling = rb_get_sibling(to_remove);
	if (to_remove->parent == &g_leaf)
		return;
	if (sibling->color == RB_RED)
	{
		rb_rotate(to_remove->parent, to_remove->dir_from_parent);
		sibling->color = RB_BLACK;
		to_remove->parent->color = RB_RED;
		sibling = rb_get_sibling(to_remove);
	}
	if (sibling->children[RB_LEFT]->color == RB_BLACK
		&& sibling->children[RB_RIGHT]->color == RB_BLACK)
	{
		if (to_remove->parent->color == RB_BLACK)
		{
			sibling->color = RB_RED;
			return (rb_rebalance_last_case_rem(to_remove->parent));
		}
		to_remove->parent->color = RB_BLACK;
		sibling->color = RB_RED;
		return;
	}
	if (sibling->children[!to_remove->dir_from_parent]->color == RB_BLACK)
	{
		rb_rotate(sibling, !to_remove->dir_from_parent);
		sibling->color = RB_RED;
		rb_get_sibling(to_remove)->color = RB_BLACK;
	}
	rb_rotate(to_remove->parent, to_remove->dir_from_parent);
	to_remove->parent->parent->color = to_remove->parent->color;
	to_remove->parent->color = RB_BLACK;
	rb_get_uncle(to_remove)->color = RB_BLACK;
}

t_rb_node			*rb_remove_node(t_rb_tree *tree, t_rb_node *to_remove)
{
	t_rb_node			*inter;
	enum e_rb_direction	dir;

	if (to_remove->children[RB_LEFT] != &g_leaf
		&& to_remove->children[RB_RIGHT] != &g_leaf)
	{
		dir = rb_alternate_dir();
		inter = rb_dir_most_element(to_remove->children[dir], !dir);
		rb_swap_user_contents(&inter, &to_remove);
		return (rb_remove_node(tree, inter));
	}
	else if (to_remove->color == RB_RED)
	{
		to_remove->parent->children[to_remove->dir_from_parent] = &g_leaf;
		return (to_remove);
	}
	else if (to_remove->children[RB_RIGHT] != &g_leaf
		|| to_remove->children[RB_LEFT] != &g_leaf)
	{
		dir = ((to_remove->children[RB_RIGHT] != &g_leaf) ? RB_RIGHT : RB_LEFT);
		inter = to_remove->children[dir];
		rb_swap_user_contents(&to_remove, &inter);
		to_remove->children[dir] = &g_leaf;
		return (inter);
	}
	else
	{
		rb_rebalance_last_case_rem(to_remove);
		if (to_remove->parent == &g_leaf)
			tree->root = &g_leaf;
		else
		{
			to_remove->parent->children[to_remove->dir_from_parent] = &g_leaf;
			inter = to_remove->parent;
			while (inter->parent != &g_leaf)
				inter = inter->parent;
			tree->root = inter;
		}
		return (to_remove);
	}
}
