/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljeanteu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 20:34:49 by ljeanteu          #+#    #+#             */
/*   Updated: 2018/07/26 19:42:34 by ljeanteu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"
#include "ft_btree_rb.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST(x) {fprintf(stderr, "%s (%s): %d %d %d %d %d\n", #x, (x)->data, (x) == (x)->parent, (x) == (x)->left, (x) == (x)->right, (x)->right?(x) != (x)->right->parent:0, (x)->left?(x) != (x)->left->parent:0);}

#define INSERT(a, b, c) rb_insert(a, b, c)

void	show(void *a)
{
	printf("%s \n", a);
}

void	good_show(t_rb_node *a, int level, int is_first_elem)
{
	if (is_first_elem)
		printf("\n%d:", level);
	printf("\t%c %s", (a->color ? 'R' : 'B'), a->data);
}

int		cmpfunc(void *a, void *b)
{
	return (strcmp((char *)a, (char *)b));
}

void	freefunc(void *a)
{
	(void)a;
}

int		main(int argc, char **argv)
{
	t_rb_node	*begin;
	int			i;
	char		*result;

	begin = NULL;
	i = 1;
	while (i < argc)
	{
		printf("%s ", argv[i]);
		INSERT(&begin, argv[i], &cmpfunc);
		i++;
	}
	printf("\n\n");
	rb_apply_prefix(begin, &show);
	printf("\n");
	rb_apply_infix(begin, &show);
	printf("\n");
	rb_apply_suffix(begin, &show);
	printf("\n\n");
	i = 1;
	while (i < argc)
	{
		result = rb_search_item(begin, argv[i], &cmpfunc);
		show(result);
		i += 2;
	}
	printf("\n");
	printf("%d \n", rb_level_count(begin));
	rb_apply_by_level(begin, &good_show);
	fflush(stdout);
/*	if (argc > 1)
		rb_remove(&begin, "2", &cmpfunc, &freefunc);
	rb_apply_by_level(begin, &good_show);*/
	return (0);
}

void	rb_apply_prefix(t_rb_node *root, void (*applyf)(void *))
{
	if (root == NULL)
		return ;
	applyf(root->data);
	rb_apply_prefix(root->left, applyf);
	rb_apply_prefix(root->right, applyf);
}

void	rb_apply_infix(t_rb_node *root, void (*applyf)(void *))
{
	if (root == NULL)
		return ;
	rb_apply_prefix(root->left, applyf);
	applyf(root->data);
	rb_apply_prefix(root->right, applyf);
}

void	rb_apply_suffix(t_rb_node *root, void (*applyf)(void *))
{
	if (root == NULL)
		return ;
	rb_apply_prefix(root->left, applyf);
	rb_apply_prefix(root->right, applyf);
	applyf(root->data);
}

void	*rb_search_item(t_rb_node *root, void *item_ref,
			int (*cmpf)(void *, void *))
{
	int	compared;

	if (root == NULL)
		return (NULL);
	compared = cmpf(item_ref, root->data);
	if (compared < 0)
		return (rb_search_item(root->left, item_ref, cmpf));
	else if (compared == 0)
		return (root->data);
	else
		return (rb_search_item(root->right, item_ref, cmpf));
}

int		rb_level_count(t_rb_node *root)
{
	int	left_val;
	int	right_val;

	left_val = 0;
	if (root->left != NULL)
		left_val = 1 + rb_level_count(root->left);
	right_val = 0;
	if (root->right != NULL)
		right_val = 1 + rb_level_count(root->right);
	return ((left_val > right_val) ? left_val : right_val);
}

void	push_queue2(t_queue2 **front, t_queue2 **back, t_rb_node *data,
			int level)
{
	t_queue2	*new_elem;

	new_elem = malloc(sizeof(*new_elem));
	new_elem->data = data;
	new_elem->level = level;
	new_elem->next = NULL;
	if (*back == NULL)
		*front = new_elem;
	else
		(*back)->next = new_elem;
	*back = new_elem;
}

void	pop_queue2(t_queue2 **front, t_queue2 **back)
{
	t_queue2	*to_remove;

	if (*front == NULL)
		return ;
	to_remove = *front;
	*front = to_remove->next;
	if (*back == to_remove)
		*back = NULL;
	free(to_remove);
}

void	rb_apply_by_level(t_rb_node *root,
			void (*applyf)(t_rb_node *item, int current_level, int is_first_elem))
{
	t_rb_node	*node;
	t_queue2 *q_front;
	t_queue2 *q_back;
	int		level;

	q_front = NULL;
	q_back = NULL;
	level = -1;
	push_queue2(&q_front, &q_back, root, 0);
	while (q_front != NULL)
	{
		node = q_front->data;
		applyf(node, q_front->level, (q_front->level != level));
		level = q_front->level;
		if (node->left)
			push_queue2(&q_front, &q_back, node->left, level + 1);
		if (node->right)
			push_queue2(&q_front, &q_back, node->right, level + 1);
		pop_queue2(&q_front, &q_back);
	}
}
