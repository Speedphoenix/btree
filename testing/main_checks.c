#include "testing.h"

void	check_single_node(t_rb_tree *cont, t_rb_node *what, const char *msg)
{
	ASSERT_TRUE(what != &g_leaf, msg)
	ASSERT_TRUE(what->dir_from_parent == RB_LEFT ||
		what->dir_from_parent == RB_RIGHT, msg)
	if (what->parent == &g_leaf)
		ASSERT_EQUALS_P(cont->root, what, msg)
	else
		ASSERT_EQUALS_P(what, what->parent->children[what->dir_from_parent],
			msg)
	if (what->children[RB_LEFT] != &g_leaf)
	{
		ASSERT_EQUALS(what->children[RB_LEFT]->dir_from_parent, RB_LEFT, msg)
		ASSERT_EQUALS_P(what->children[RB_LEFT]->parent, what, msg)
	}
	if (what->children[RB_RIGHT] != &g_leaf)
	{
		ASSERT_EQUALS(what->children[RB_RIGHT]->dir_from_parent, RB_RIGHT, msg)
		ASSERT_EQUALS_P(what->children[RB_RIGHT]->parent, what, msg)
	}
	if (what != cont->begin)
		EXPECT_TRUE(cont->compare(cont->begin->key, what->key), msg)
	if (what != cont->end)
		EXPECT_TRUE(cont->compare(what->key, cont->end->key), msg)
}

void	check_single_node_rb(t_rb_tree *cont, t_rb_node *what, const char *msg)
{
	check_single_node(cont, what, msg);
	ASSERT_TRUE(what->color == RB_BLACK || what->color == RB_RED, msg)
	if (cont->root == what)
		ASSERT_EQUALS(what->color, RB_BLACK, msg)
	if(what->color == RB_RED)
	{
		ASSERT_EQUALS(what->children[RB_LEFT]->color, RB_BLACK, msg)
		ASSERT_EQUALS(what->children[RB_RIGHT]->color, RB_BLACK, msg)
	}
}

size_t	recurs_check(t_rb_tree *cont, t_rb_node *root, const char *msg)
{
	t_rb_node	*curr;
	size_t		rep;

	if (root == &g_leaf)
		return (0);
	rep = 1;
	check_single_node(cont, root, msg);
	curr = root->children[RB_LEFT];
	if (curr != &g_leaf)
	{
		ASSERT_TRUE_MORE(cont->compare(curr->key, root->key), msg,
			display_node(root); display_node(curr);)
		rep += recurs_check(cont, curr, msg);
	}
	curr = root->children[RB_RIGHT];
	if (curr != &g_leaf)
	{
		ASSERT_TRUE_MORE(cont->compare(root->key, curr->key), msg,
			display_node(root); display_node(curr);)
		rep += recurs_check(cont, curr, msg);
	}
	return (rep);
}

int		recurs_check_rb(t_rb_tree *cont, t_rb_node *root, const char *msg)
{
	int		right_rep;
	int		left_rep;

	if (root == &g_leaf)
		return (1);
	check_single_node_rb(cont, root, msg);
	left_rep = recurs_check_rb(cont, root->children[RB_LEFT], msg);
	right_rep = recurs_check_rb(cont, root->children[RB_RIGHT], msg);
	ASSERT_EQUALS_MORE(left_rep, right_rep, msg, display_node(root);)
	return ((root->color == RB_BLACK) + left_rep);
}

void	check_tree(t_rb_tree *cont, const char *msg)
{
	size_t	nb_elements;

	check_leaf(&g_leaf, msg);
	nb_elements = recurs_check(cont, cont->root, msg);
	EXPECT_EQUALS_TYPE(cont->nb_elements, nb_elements, msg, "%ld")
}

void	check_tree_rb(t_rb_tree *cont, const char *msg)
{
	check_tree(cont, msg);
	recurs_check_rb(cont, cont->root, msg);
}

void	check_leaf(t_rb_node *the_leaf, const char *msg)
{
	ASSERT_EQUALS_P(the_leaf, &g_leaf, msg)
	ASSERT_EQUALS_P(the_leaf->children[RB_RIGHT], NULL, msg)
	ASSERT_EQUALS_P(the_leaf->children[RB_LEFT], NULL, msg)
	ASSERT_EQUALS(the_leaf->color, RB_BLACK, msg)
	ASSERT_EQUALS_P(the_leaf->key, NULL, msg)
	ASSERT_EQUALS_P(the_leaf->data, NULL, msg)
}
