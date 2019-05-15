#include "node.h"

t_rb_node	*rb_dir_most_element(t_rb_node *root, enum e_rb_direction dir)
{
	if (root == &g_leaf)
		return (NULL);
	if (root->children[dir] == &g_leaf)
		return (root);
	return (rb_dir_most_element(root->children[dir], dir));
}

t_rb_node	*rb_node_in_dir(t_rb_node *where, enum e_rb_direction dir,
				int fromChild)
{
	if (where == &g_leaf)
		return (NULL);
	if (!fromChild && where->children[dir] != &g_leaf)
		return (rb_dir_most_element(where->children[dir], !dir));
	if (where->parent == &g_leaf)
		return (NULL);
	if (where->dir_from_parent != dir)
		return (where->parent);
	return (rb_node_in_dir(where->parent, dir, 1));
}

t_rb_node	*rb_next_node(t_rb_node *where)
{
	return (rb_node_in_dir(where, RB_RIGHT, 0));
}

t_rb_node	*rb_prev_node(t_rb_node *where)
{
	return (rb_node_in_dir(where, RB_LEFT, 0));
}
