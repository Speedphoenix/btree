/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_rb.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljeanteu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 16:37:43 by ljeanteu          #+#    #+#             */
/*   Updated: 2018/07/26 19:41:35 by ljeanteu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BTREE_RB_H
# define FT_BTREE_RB_H

# ifndef HAHA
#  define HAHA
enum					e_rb_color
{
	RB_BLACK,
	RB_RED
};
# endif

typedef struct			s_rb_node
{
	struct s_rb_node	*parent;
	struct s_rb_node	*left;
	struct s_rb_node	*right;
	void				*data;
	enum e_rb_color		color;
}						t_rb_node;

void					rb_insert(struct s_rb_node **root, void *data,
							int (cmpf)(void *, void *));
void					rb_remove(struct s_rb_node **root, void *data,
							int (*cmpf)(void *, void *), void (*freef)(void *));

void	rb_apply_prefix(t_rb_node *root, void (*applyf)(void *));
void	rb_apply_infix(t_rb_node *root, void (*applyf)(void *));
void	rb_apply_suffix(t_rb_node *root, void (*applyf)(void *));
void	*rb_search_item(t_rb_node *root, void *item_ref,
			int (*cmpf)(void *, void *));
int		rb_level_count(t_rb_node *root);
void	rb_apply_by_level(t_rb_node *root,
			void (*applyf)(t_rb_node *item, int current_level, int is_first_elem));

typedef struct		s_queue2
{
	struct s_queue2	*next;
	t_rb_node		*data;
	int				level;
}					t_queue2;

void	push_queue2(t_queue2 **front, t_queue2 **back, t_rb_node *data,
			int level);
void	pop_queue2(t_queue2 **front, t_queue2 **back);

#endif
