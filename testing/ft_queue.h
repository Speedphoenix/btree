#ifndef FT_BTREE_H
# define FT_BTREE_H

# include "btree.h"

typedef struct			s_queue
{
	struct s_queue		*next;
	struct s_rb_node	*data;
	int					level;
}						t_queue;

#endif
