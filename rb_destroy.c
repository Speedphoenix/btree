#include "btree.h"
#include "node.h"
#include "stdlib.h"

void	rb_tree_vacate(t_rb_tree *tree,
			void (*applyf)(t_key, t_data))
{
	rb_subtree_destroy(tree->root, applyf);
	tree->root = &g_leaf;
	tree->begin = &g_leaf;
	tree->end = &g_leaf;
	tree->nb_elements = 0;
}

void	rb_tree_destroy(t_rb_tree *tree,
			void (*applyf)(t_key, t_data))
{
	rb_subtree_destroy(tree->root, applyf);
	free(tree);
}

void	rb_node_destroy(t_rb_node *what)
{
	free(what);
}

void	rb_subtree_destroy(t_rb_node *root,
			void (*applyf)(t_key, t_data))
{
	if (root == &g_leaf)
		return;
	rb_subtree_destroy(root->children[RB_LEFT], applyf);
	rb_subtree_destroy(root->children[RB_RIGHT], applyf);
	applyf(root->key, root->data);
	rb_node_destroy(root);
}
