#ifndef TESCTING_H
# define TESCTING_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "btree.h"
# include "node.h"
# include "time.h"

# ifndef NOCOL
#  define RST	"\x1B[0m"
#  define RED	"\x1B[31m"
#  define GRN	"\x1B[32m"
#  define YEL	"\x1B[33m"
#  define BLU	"\x1B[34m"
#  define MAG	"\x1B[35m"
#  define CYN	"\x1B[36m"
# else
#  define RST
#  define RED
#  define GRN
#  define YEL
#  define BLU
#  define MAG
#  define CYN
# endif


# define E(x) { fprintf(stderr, YEL "%s, line %d:" CYN " %s %d\n" RST,			\
	__FILE__, __LINE__, #x, (x));}
# define EP(x) { fprintf(stderr, YEL "%s, line %d:" CYN " %s %p\n" RST,			\
	__FILE__, __LINE__, #x, (x));}
# define ES(x) { fprintf(stderr, YEL "%s, line %d:" GRN " %s\n" RST,			\
	__FILE__, __LINE__, (x));}

# define GENERIC_PREASSERT(genericmsg, msg)										\
fprintf(stderr, genericmsg YEL " file: %s, line: %d\n" RST, __FILE__,			\
	__LINE__);																	\
if (msg)																		\
	fprintf(stderr, CYN "msg: %s\n" RST, msg);

# define GENERIC_POSTASSERT(exit_if_fail, failaction)							\
failaction;																		\
if (exit_if_fail)																\
	exit(1);

# define ASSERT_EQUALS_ALL(a, b, exit_if_fail, msg, failaction, type) {			\
if ((a) != (b))																	\
{																				\
	GENERIC_PREASSERT("Assert equals " RED "failed." RST, msg)					\
	fprintf(stderr, RED "%s" RST " (" RED type RST ") not equal to "			\
		RED "%s" RST " (" RED type RST ")\n\n",									\
		#a, (a), #b, (b));														\
	GENERIC_POSTASSERT(exit_if_fail, failaction)								\
}																				\
}

# define ASSERT_EQUALS_MORE_TYPE(a, b, msg, failaction, type)					\
ASSERT_EQUALS_ALL(a, b, 1, msg, failaction, type)
# define EXPECT_EQUALS_MORE_TYPE(a, b, msg, failaction, type)					\
ASSERT_EQUALS_ALL(a, b, 0, msg, failaction, type)

# define ASSERT_EQUALS_MORE(a, b, msg, failaction)								\
ASSERT_EQUALS_ALL(a, b, 1, msg, failaction, "%d")
# define EXPECT_EQUALS_MORE(a, b, msg, failaction)								\
ASSERT_EQUALS_ALL(a, b, 0, msg, failaction, "%d")

# define ASSERT_EQUALS_TYPE(a, b, msg, type)									\
ASSERT_EQUALS_ALL(a, b, 1, msg, , type)
# define EXPECT_EQUALS_TYPE(a, b, msg, type)									\
ASSERT_EQUALS_ALL(a, b, 0, msg, , type)

# define ASSERT_EQUALS_P(a, b, msg)												\
ASSERT_EQUALS_ALL(a, b, 1, msg, , "%p")
# define EXPECT_EQUALS_P(a, b, msg)												\
ASSERT_EQUALS_ALL(a, b, 0, msg, , "%p")

# define ASSERT_EQUALS(a, b, msg)												\
ASSERT_EQUALS_ALL(a, b, 1, msg, , "%d")
# define EXPECT_EQUALS(a, b, msg)												\
ASSERT_EQUALS_ALL(a, b, 0, msg, , "%d")

# define ASSERT_TRUE_ALL(a, exit_if_fail, msg, failaction) {					\
if (!(a))																		\
{																				\
	GENERIC_PREASSERT("Assert true failed.", msg)								\
	fprintf(stderr, RED "%s" RST " (" RED "%d" RST ") not true\n\n",			\
		#a, (int)(a));															\
	GENERIC_POSTASSERT(exit_if_fail, failaction)								\
}																				\
}

# define ASSERT_TRUE_MORE(a, msg, failaction)									\
ASSERT_TRUE_ALL(a, 1, msg, failaction)
# define EXPECT_TRUE_MORE(a, msg, failaction)									\
ASSERT_TRUE_ALL(a, 0, msg, failaction)

# define ASSERT_TRUE(a, msg)													\
ASSERT_TRUE_ALL(a, 1, msg,)
# define EXPECT_TRUE(a, msg)													\
ASSERT_TRUE_ALL(a, 0, msg,)

void	check_single_node(t_rb_tree *cont, t_rb_node *what, const char *msg);
void	check_single_node_rb(t_rb_tree *cont, t_rb_node *what, const char *msg);

void	check_tree(t_rb_tree *cont, const char *msg);
void	check_tree_rb(t_rb_tree *cont, const char *msg);
void	check_leaf(t_rb_node *the_leaf, const char *msg);
size_t	recurs_check(t_rb_tree *cont, t_rb_node *root, const char *msg);
int		recurs_check_rb(t_rb_tree *cont, t_rb_node *root, const char *msg);

void	display_node(t_rb_node *what);
void	display_test(t_key key, t_data data);
void	display_tree(t_rb_tree *cont);
void	display_col(enum e_rb_color what);

void	display_in_level(t_rb_node *item, int current_level,
			int is_first_elem);
void	btree_apply_by_level(t_rb_tree *tree,
			void (*applyf)(t_rb_node *item, int current_level,
				int is_first_elem));

#endif
