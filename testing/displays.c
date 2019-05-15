#include "testing.h"

void	display_test(t_key key, t_data data)
{
	fprintf(stderr, "k: %d, data: %s", *((int*)key), (char *)data);
}

void	display_col(enum e_rb_color what)
{
	fprintf(stderr, "(");
	if (what == RB_RED)
		fprintf(stderr, RED);
	else
		fprintf(stderr, BLU);
	fprintf(stderr, "col %d", what);
	fprintf(stderr, RST);
	fprintf(stderr, ")");
}

void	display_node(t_rb_node *what)
{
	fprintf(stderr, "\n");
	if (what == &g_leaf)
	{
		fprintf(stderr, "This is a leaf\n\n");
		return;
	}
	fprintf(stderr, "this: ");
	display_col(what->color);
	display_test(what->key, what->data);
	fprintf(stderr, "\nParent: ");
	display_col(what->parent->color);
	if (what->parent != &g_leaf)
	{
		display_test(what->parent->key, what->parent->data);
	}
	else
		fprintf(stderr, "leaf");
	fprintf(stderr, "\nchildren:\nLeft: ");
	display_col(what->children[RB_LEFT]->color);
	if (what->children[RB_LEFT] != &g_leaf)
	{
		display_test(what->children[RB_LEFT]->key,
			what->children[RB_LEFT]->data);
	}
	else
		fprintf(stderr, "leaf");
	fprintf(stderr, " Right: ");
	display_col(what->children[RB_RIGHT]->color);
	if (what->children[RB_RIGHT] != &g_leaf)
	{
		display_test(what->children[RB_RIGHT]->key,
			what->children[RB_RIGHT]->data);
	}
	else
		fprintf(stderr, "leaf");
	fprintf(stderr, "\n\n");
}

void	display_in_level(t_rb_node *item, int current_level,
			int is_first_elem)
{
	if (is_first_elem)
		fprintf(stderr, "\n" GRN "%d" RST, current_level);
	else
		fprintf(stderr, "\t;");
	if (item == &g_leaf)
	{
		fprintf(stderr, "leaf ");
		return;
	}
	fprintf(stderr, " ");
	display_col(item->color);
	display_test(item->key, item->data);
}

void	display_contents(t_key key, t_data value)
{
	display_test(key, value);
	fprintf(stderr, "\n");
}

void	display_tree(t_rb_tree *cont)
{
	t_rb_node	*curr;

	E(rb_level_count(cont))
	E((int)cont->nb_elements)
	ES("\nDefault:");
	btree_traverse(cont, display_contents);
	ES("\nPrefix:");
	btree_traverse_meth(cont, TRAVERSE_PREFIX, display_contents);
	ES("\nInfix:");
	btree_traverse_meth(cont, TRAVERSE_INFIX, display_contents);
	ES("\nPostfix:");
	btree_traverse_meth(cont, TRAVERSE_POSTFIX, display_contents);
	fprintf(stderr, "\n");

	ES("\nBy level:");
	btree_apply_by_level(cont, display_in_level);
	fprintf(stderr, "\n");
	fprintf(stderr, "\n");

	ES("\nUsing the next function:")
	curr = cont->begin;
	while (curr != &g_leaf && curr != NULL)
	{
		display_node(curr);
		curr = rb_next_node(curr);
	}

	ES("\nUsing the prev function:")
	curr = cont->end;
	while (curr != &g_leaf && curr != NULL)
	{
		display_node(curr);
		curr = rb_prev_node(curr);
	}
}
