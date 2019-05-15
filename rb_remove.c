#include "btree.h"
#include "node.h"

t_data	rb_remove(t_rb_tree *tree, t_key key)
{
	t_rb_node	*to_remove;
	t_data		rep;

	to_remove = rb_find_node(tree, key);
	if ((to_remove == &g_leaf)
		|| tree->compare(to_remove->key, key)
		|| tree->compare(key, to_remove->key))
		return (NULL);
	rep = to_remove->data;
	// decrement tree->nb_elements
	// get new begin and end pointers for the tree
	return (rep);
}

/*
**	returns whether an edge of the tree has been deleted
**	TODO: make the direction in which we take the innermost child
**	alternate/random
*/
void	rb_remove_node(t_rb_tree *tree, t_rb_node *to_remove)
{
	t_rb_node			*inter;
	enum e_rb_direction	dir;

	if (to_remove->children[RB_LEFT] != &g_leaf
		&& to_remove->children[RB_RIGHT] != &g_leaf)
	{
		dir = RB_LEFT;
		inter = rb_dir_most_element(to_remove->children[dir], !dir);
		rb_swap_user_contents(inter, to_remove);
		rb_remove_node(tree, inter);
	}
	else if(1)
	{
	}
}
