#include "btree.h"
#include "node.h"

const t_trav	g_trav[] =
{
	&btree_recurs_prefix,
	&btree_recurs_infix,
	&btree_recurs_postfix
};

void		btree_recurs_prefix(t_rb_node *root,
				void (*applyf)(t_key, t_data))
{
	if (root == &g_leaf)
		return ;
	applyf(root->key, root->data);
	btree_recurs_prefix(root->children[RB_LEFT], applyf);
	btree_recurs_prefix(root->children[RB_RIGHT], applyf);
}

void		btree_recurs_infix(t_rb_node *root,
				void (*applyf)(t_key, t_data))
{
	if (root == &g_leaf)
		return ;
	btree_recurs_infix(root->children[RB_LEFT], applyf);
	applyf(root->key, root->data);
	btree_recurs_infix(root->children[RB_RIGHT], applyf);
}

void		btree_recurs_postfix(t_rb_node *root,
				void (*applyf)(t_key, t_data))
{
	if (root == &g_leaf)
		return ;
	btree_recurs_postfix(root->children[RB_LEFT], applyf);
	btree_recurs_postfix(root->children[RB_RIGHT], applyf);
	applyf(root->key, root->data);
}

void		btree_traverse(t_rb_tree *cont, void (*applyf)(t_key, t_data))
{
	g_trav[TRAVERSE_INFIX](cont->root, applyf);
}


void		btree_traverse_meth(t_rb_tree *cont, unsigned method,
				void (*applyf)(t_key, t_data))
{
	if (method >= 3)
		return;
	g_trav[method](cont->root, applyf);
}
