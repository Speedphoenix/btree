#include "testing.h"

int		intcompare(int a, int b)
{
	return (a < b);
}

int		compare(void *keya, void *keyb)
{
	return (intcompare(*((int*)keya), *((int*)keyb)));
}

void	*newint(int val)
{
	int	*rep;

	rep = malloc(sizeof(int));
	*rep = val;
	return ((void*)rep);
}

void		add_n_checks(t_rb_tree *tree, int key, char *value)
{
	t_rb_node		*node;
	t_rb_node		*nodec;

	node = rb_create_node(newint(key), value); 
	nodec = rb_stupid_insert(tree, node);
	check_single_node(tree, node, "created node test");
	ASSERT_EQUALS_P(node, nodec, "inserted node check")
	check_tree(tree, "one elem test");
	ASSERT_TRUE(!rb_tree_is_empty(tree), "should not be empty")
	ASSERT_EQUALS_P(rb_at(tree, &key), value, "check the inserted value")
	ASSERT_EQUALS(strcmp(rb_at(tree, &key), value), 0, "")
}

void		add_n_checks_rb(t_rb_tree *tree, int key, char *value)
{
	E(key)
	rb_insert(tree, newint(key), value);
	display_tree(tree);
	check_tree_rb(tree, "after an addition");
}

t_rb_tree	*test_tree()
{
	t_rb_tree		*tree;

	tree = rb_create_tree(compare);
	ASSERT_TRUE(rb_tree_is_empty(tree), "should be empty")
	ASSERT_EQUALS(rb_level_count(tree), 0, "should be empty")
	check_tree_rb(tree, "empty test");
	return (tree);
}

void		fill_tree_balanced(t_rb_tree *tree)
{
	add_n_checks(tree, 7, "");
	add_n_checks(tree, 3, "");
	add_n_checks(tree, 11, "");
	add_n_checks(tree, 1, "");
	add_n_checks(tree, 5, "");
	add_n_checks(tree, 9, "");
	add_n_checks(tree, 13, "");
	add_n_checks(tree, 0, "");
	add_n_checks(tree, 2, "");
	add_n_checks(tree, 4, "");
	add_n_checks(tree, 6, "");
	add_n_checks(tree, 8, "");
	add_n_checks(tree, 10, "");
	add_n_checks(tree, 12, "");
	add_n_checks(tree, 14, "");
}

void		fill_tree_balanced_diff_order(t_rb_tree *tree)
{
	add_n_checks(tree, 7, "");
	add_n_checks(tree, 3, "");
	add_n_checks(tree, 1, "");
	add_n_checks(tree, 0, "");
	add_n_checks(tree, 2, "");
	add_n_checks(tree, 5, "");
	add_n_checks(tree, 4, "");
	add_n_checks(tree, 6, "");
	add_n_checks(tree, 11, "");
	add_n_checks(tree, 9, "");
	add_n_checks(tree, 8, "");
	add_n_checks(tree, 10, "");
	add_n_checks(tree, 13, "");
	add_n_checks(tree, 12, "");
	add_n_checks(tree, 14, "");
}

void		fill_tree_rand(t_rb_tree *tree, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if (!rb_insert(tree, newint(rand() % (nb * 10)), ""))
		{
			//ES("tryed inserting an existing key")
			//E(i)
		}
		//else
		//	check_tree_rb(tree, "intermediary rb check");
		i++;
	}
}

void		fill_tree_ordered(t_rb_tree *tree, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if (!rb_insert(tree, newint(i), ""))
		{
			ES("tryed inserting an existing key")
			E(i)
		}
		else
			check_tree_rb(tree, "intermediary rb check");
		i++;
	}
}

void		fill_tree_bal(t_rb_tree *tree)
{
	add_n_checks_rb(tree, 7, "");
	add_n_checks_rb(tree, 3, "");
	add_n_checks_rb(tree, 1, "");
	add_n_checks_rb(tree, 0, "");
	add_n_checks_rb(tree, 2, "");
	add_n_checks_rb(tree, 5, "");
	add_n_checks_rb(tree, 4, "");
	add_n_checks_rb(tree, 6, "");
	add_n_checks_rb(tree, 11, "");
	add_n_checks_rb(tree, 9, "");
	add_n_checks_rb(tree, 8, "");
	add_n_checks_rb(tree, 10, "");
	add_n_checks_rb(tree, 13, "");
	add_n_checks_rb(tree, 12, "");
	add_n_checks_rb(tree, 14, "");
}

int			main(int argc, char **argv)
{
	t_rb_tree		*tree;

	(void) argc;
	(void) argv;
	srand(time(NULL));
	ASSERT_EQUALS(0, 0, "")
	EXPECT_EQUALS(1, 1, "")
	ASSERT_EQUALS_TYPE(1.5, 1.5, "", "%f")
	ASSERT_EQUALS(0, 0, "Some equivalent vals")
	ASSERT_EQUALS(1, 1, "Some equivalent vals")

	ASSERT_TRUE(1, "some message1")
	ASSERT_TRUE(1, "")
	EXPECT_TRUE(24 == 24, "some message2")
	EXPECT_TRUE(24 != 23, "some message3")
	ASSERT_TRUE(25, "some message4")

	tree = test_tree();
	fill_tree_bal(tree);
	display_tree(tree);
	check_tree_rb(tree, "rb check");
	fill_tree_ordered(tree, 4000);
	check_tree_rb(tree, "rb check");
	display_tree(tree);
	fill_tree_rand(tree, 4000);
	check_tree_rb(tree, "rb check");
	display_tree(tree);
	E((int)tree->nb_elements)

	return (0);
}
