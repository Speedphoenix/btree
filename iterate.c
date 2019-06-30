#include "node.h"

const t_trav	g_trav[] =
{
	&rb_recurs_prefix,
	&rb_recurs_infix,
	&rb_recurs_postfix
};

void		rb_recurs_prefix(t_rb_node *root,
				void (*applyf)(t_key, t_data))
{
	if (root == &g_leaf)
		return ;
	applyf(root->key, root->data);
	rb_recurs_prefix(root->children[RB_LEFT], applyf);
	rb_recurs_prefix(root->children[RB_RIGHT], applyf);
}

void		rb_recurs_infix(t_rb_node *root,
				void (*applyf)(t_key, t_data))
{
	if (root == &g_leaf)
		return ;
	rb_recurs_infix(root->children[RB_LEFT], applyf);
	applyf(root->key, root->data);
	rb_recurs_infix(root->children[RB_RIGHT], applyf);
}

void		rb_recurs_postfix(t_rb_node *root,
				void (*applyf)(t_key, t_data))
{
	if (root == &g_leaf)
		return ;
	rb_recurs_postfix(root->children[RB_LEFT], applyf);
	rb_recurs_postfix(root->children[RB_RIGHT], applyf);
	applyf(root->key, root->data);
}

void		rb_traverse(t_rb_tree *cont, void (*applyf)(t_key, t_data))
{
	g_trav[TRAVERSE_INFIX](cont->root, applyf);
}


void		rb_traverse_meth(t_rb_tree *cont, unsigned method,
				void (*applyf)(t_key, t_data))
{
	if (method >= 3)
		return;
	g_trav[method](cont->root, applyf);
}
