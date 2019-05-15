#include "node.h"

/*
**	Will return a pointer to the parent if the key isn't in the tree
*/
t_rb_node	*rb_find_node(t_rb_tree *container, t_key key)
{
	t_rb_node	*curr;
	t_rb_node	*parent;

	parent = &g_leaf;
	curr = container->root;
	while (curr != &g_leaf)
	{
		parent = curr;
		if (container->compare(key, curr->key))
			curr = parent->children[RB_LEFT];
		else if (container->compare(curr->key, key))
			curr = parent->children[RB_RIGHT];
		else
			break;
	}
	return (parent);
}

int			rb_tree_is_empty(t_rb_tree *container)
{
	return (container->nb_elements == 0);
}

t_data		rb_at(t_rb_tree *container, t_key key)
{
	t_rb_node	*where;
	
	where = rb_find_node(container, key);
	if (where == &g_leaf)
		return (NULL);
	if (container->compare(where->key, key)
		|| container->compare(key, where->key))
		return (NULL);
	return (where->data);
}

int		rb_level_count_recurs(t_rb_node *root)
{
	int	left_val;
	int	right_val;

	if (root == &g_leaf)
		return (0);
	left_val = rb_level_count_recurs(root->children[RB_LEFT]);
	right_val = rb_level_count_recurs(root->children[RB_RIGHT]);
	return (1 + ((left_val > right_val) ? left_val : right_val));
}

int		rb_level_count(t_rb_tree *tree)
{
	return (rb_level_count_recurs(tree->root));
}
