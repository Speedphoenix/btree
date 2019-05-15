/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljeanteu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 13:49:27 by ljeanteu          #+#    #+#             */
/*   Updated: 2018/07/25 14:29:39 by ljeanteu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BTREE_H
# define FT_BTREE_H

# ifndef HAHA
#  define HAHA
enum					e_rb_color
{
	RB_BLACK,
	RB_RED
};
# endif

typedef struct		s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
	enum e_rb_color		color;
}					t_btree;

t_btree		*btree_create_node(void *item);
void		btree_apply_prefix(t_btree *root, void (*applyf)(void *));
void		btree_apply_infix(t_btree *root, void (*applyf)(void *));
void		btree_apply_suffix(t_btree *root, void (*applyf)(void *));
void		btree_insert_data(t_btree **root, void *item,
				int (*cmpf)(void *, void *));
void		*btree_search_item(t_btree *root, void *data_ref,
				int (*cmpf)(void *, void *));
int			btree_level_count(t_btree *root);
void		btree_apply_by_level(t_btree *root,
			void (*applyf)(void *item, int current_level, int is_first_elem));

typedef struct		s_queue
{
	struct s_queue	*next;
	t_btree			*data;
	int				level;
}					t_queue;

void	push_queue(t_queue **front, t_queue **back, t_btree *data, int level);
void	pop_queue(t_queue **front, t_queue **back);

#endif
