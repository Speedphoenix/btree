/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljeanteu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 16:55:25 by ljeanteu          #+#    #+#             */
/*   Updated: 2018/07/26 12:15:19 by ljeanteu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree_rb.h"
#include <stdlib.h>

#include <stdio.h>
#define E(x) {fprintf(stderr, "%s: %d\n", #x, (x));}
#define ES(x) {fprintf(stderr, "%s: %s\n", #x, (x));}
#define EP(x) {fprintf(stderr, "%s: %p\n", #x, (x));}

#define TEST(x) {fprintf(stderr, "%s (%s): %d %d %d %d %d\n", #x, (x)->data, (x) == (x)->parent, (x) == (x)->left, (x) == (x)->right, (x)->right?(x) != (x)->right->parent:0, (x)->left?(x) != (x)->left->parent:0);}

void		rb_rotate2(t_rb_node *node, int right)
{
	t_rb_node	*contender;

	contender = right ? node->left : node->right;
	if (!contender)
		return ;
	contender->parent = node->parent;
	node->parent = contender;
	if (right)
	{
		node->left = contender->right;
		contender->right = node;
		if (node->left)
			node->left->parent = node;
	}
	else
	{
		node->right = contender->left;
		contender->left = node;
		if (node->right)
			node->right->parent = node;
	}
	if (contender->parent && (node == contender->parent->right))
		contender->parent->right = contender;
	else if (contender->parent)
		contender->parent->left = contender;
}

void		end_cases(t_rb_node *rem, t_rb_node *bro, int is_left)
{
	E(650)
	if (rem->parent->color == RB_RED && bro->color == RB_BLACK &&
			!bro->right && !bro->left)
	{
		E(651)
		rem->parent->color = RB_BLACK;
		bro->color = RB_RED;
		return ;
	}
	if (is_left ? bro->right->color == RB_BLACK : bro->left->color == RB_BLACK)
	{
		E(652)
		bro->color = RB_RED;
		if (is_left)
			bro->left->color = RB_BLACK;
		else
			bro->right->color = RB_BLACK;
		rb_rotate2(bro, is_left);
		bro = bro->parent;
	}
	E(653)
	bro->color = rem->parent->color;
	rem->parent->color = RB_BLACK;
	if (is_left)
		bro->right->color = RB_BLACK;
	else
		bro->left->color = RB_BLACK;
	E(654)
	rb_rotate2(rem->parent, !is_left);
}

void		last_case_rebalance(t_rb_node *rem)
{
	t_rb_node	*bro;
	int			is_left;

	TEST(rem)
	if (rem->parent == NULL)
		return ;
	E(60)
	TEST(rem->parent)
	is_left = (rem == rem->parent->left);
	bro = is_left ? rem->parent->right : rem->parent->left;
	TEST(bro)
	if (bro->color == RB_RED)
	{
		E(61)
		rb_rotate2(rem->parent, !is_left);
		rem->parent->color = RB_RED;
		bro->color = RB_BLACK;
		bro = is_left ? rem->parent->right : rem->parent->left;
		E(62)
	}
	if (rem->parent->color == bro->color == RB_BLACK)
	{
		E(63)
		bro->color = RB_RED;
		last_case_rebalance(rem->parent);
		E(64)
		return ;
	}
	E(65)
	end_cases(rem, bro, is_left);
}

t_rb_node	*remove_it(t_rb_node **to_remove)
{
	void		*inter;
	t_rb_node	*rem;

	rem = *to_remove;
	E(1)
	ES((*to_remove)->data)
	if ((*to_remove)->left && (*to_remove)->right)
	{
		E(2)
		to_remove = &((*to_remove)->right);
		while ((*to_remove)->left != NULL)
			to_remove = &((*to_remove)->left);
		inter = (*to_remove)->data;
		(*to_remove)->data = rem->data;
		rem->data = inter;
		E(20)
		rem = remove_it(to_remove);
		E(21)
	}	//swap with inner most other node + recursive call
	else if (rem->color == RB_RED)
	{
		E(3)
		*to_remove = NULL; //replace it by a leaf
	}
	else if ((rem->left || rem->right) &&
			RB_RED == (rem->left ? rem->left->color : rem->right->color))
	{E(4)
		*to_remove = rem->left ? rem->left : rem->right;
		(*to_remove)->parent = rem->parent;
		(*to_remove)->color = RB_BLACK;
		E(41)
	}	//replace to_remove by the child and paint the child black
	else
	{
		E(6)
		last_case_rebalance(rem);
		E(7)
		*to_remove = NULL;
	}
	E(8)
	return (rem);
}

void		rb_remove(struct s_rb_node **root, void *data,
				int (*cmpf)(void *, void *), void (*freef)(void *))
{
	t_rb_node	**to_remove;
	t_rb_node	*removed;
ES("-------------------------------")
	to_remove = root;
	while (*to_remove != NULL && cmpf(data, (*to_remove)->data) != 0)
	{TEST(*to_remove)
		if (cmpf(data, (*to_remove)->data) < 0)
			to_remove = &((*to_remove)->left);
		else
			to_remove = &((*to_remove)->right);
	}
	if (*to_remove == NULL)
		return ;
	TEST(*to_remove)
	E(0)
	removed = remove_it(to_remove);
	TEST(removed)
	*root = removed->parent;
	TEST(*root)
	while ((*root)->parent != NULL)
		*root = (*root)->parent;
	TEST(*root)
	freef(removed->data);
	free(removed);
}
