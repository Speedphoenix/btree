#ifndef BTREE_H
# define BTREE_H

# include <stddef.h>

# define TRAVERSE_PREFIX 0
# define TRAVERSE_INFIX 1
# define TRAVERSE_POSTFIX 2

/*
**	t_data MUST be a pointer type
*/
typedef int				t_key;
typedef void			*t_data;

# define DEFAULTKEY 0

/*
** A compare function must behave like the '<' operator
** intcompare(int *a, int *b) should behave as a < b
*/
typedef int				(*t_compare_func)(t_key, t_key);

typedef struct			s_rb_tree
{
	struct s_rb_node	*root;
	struct s_rb_node	*begin;
	struct s_rb_node	*end;
	t_compare_func		compare;
	size_t				nb_elements;
}						t_rb_tree;

t_rb_tree				*rb_create_tree(t_compare_func compare);
void					rb_init_tree(t_rb_tree *what, t_compare_func compare);
int						rb_tree_is_empty(t_rb_tree *container);
t_data					rb_at(t_rb_tree *container, t_key key);
void					btree_traverse(t_rb_tree *cont,
							void (*applyf)(t_key, t_data));
void					btree_traverse_meth(t_rb_tree *cont, unsigned method,
							void (*applyf)(t_key, t_data));
int						rb_insert(t_rb_tree *tree, t_key key, t_data data);

void					rb_tree_vacate(t_rb_tree *tree,
							void (*applyf)(t_key, t_data));
void					rb_tree_destroy(t_rb_tree *tree,
							void (*applyf)(t_key, t_data));

/*
**	Returns the value after destroying the node that contained it
*/
t_data					rb_remove(t_rb_tree *tree, t_key key);

#endif
