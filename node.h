#ifndef NODE_H
# define NODE_H

# include "btree.h"
# define RB_NBDIRS 2

enum					e_rb_direction
{
	RB_LEFT = 0,
	RB_RIGHT = 1
};

enum					e_rb_color
{
	RB_BLACK,
	RB_RED
};

typedef struct			s_rb_node
{
	struct s_rb_node	*parent;
	struct s_rb_node	*children[RB_NBDIRS];
	t_key				key;
	t_data				data;
	enum e_rb_color		color;
	enum e_rb_direction	dir_from_parent;
}						t_rb_node;

typedef void			(*t_trav)(t_rb_node *, void (*)(t_key, t_data));

extern t_rb_node		g_leaf;
extern const t_trav		g_trav[];

int						rb_level_count(t_rb_tree *tree);

t_rb_node				*rb_create_node(t_key key, t_data data);
void					rb_init_node(t_rb_node *what, t_key key, t_data data);
t_rb_node				*rb_find_node(t_rb_tree *container, t_key key);
void					rb_check_edges(t_rb_tree *cont, t_rb_node *what);
void					rb_add_child(t_rb_tree *cont, t_rb_node *what,
							t_rb_node *parent, enum e_rb_direction dir);
t_rb_node				*rb_stupid_insert(t_rb_tree *container,
							t_rb_node *what);
void					rb_swap_user_contents(t_rb_node *a, t_rb_node *b);

int						rb_rotate(t_rb_node *root, enum e_rb_direction dir);
t_rb_node				*rb_set_new_parent(t_rb_node *what, t_rb_node *parent,
							enum e_rb_direction dir);
t_rb_node				*rb_get_uncle(t_rb_node *from);
t_rb_node				*rb_get_sibling(t_rb_node *from);
t_rb_node				*rb_get_grandp(t_rb_node *from);
void					rb_correct_insert(t_rb_node *new_elem);
void					rb_insert_last_case(t_rb_node *new_el);

void					rb_node_destroy(t_rb_node *what);
void					rb_subtree_destroy(t_rb_node *root);

void					btree_recurs_prefix(t_rb_node *root,
							void (*applyf)(t_key, t_data));
void					btree_recurs_infix(t_rb_node *root,
							void (*applyf)(t_key, t_data));
void					btree_recurs_postfix(t_rb_node *root,
							void (*applyf)(t_key, t_data));
int						rb_level_count_recurs(t_rb_node *root);

t_rb_node				*rb_dir_most_element(t_rb_node *root,
							enum e_rb_direction dir);
t_rb_node				*rb_node_in_dir(t_rb_node *where,
							enum e_rb_direction dir, int fromChild);
t_rb_node				*rb_next_node(t_rb_node *where);
t_rb_node				*rb_prev_node(t_rb_node *where);

#endif
