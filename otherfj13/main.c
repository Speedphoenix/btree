/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljeanteu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 20:34:49 by ljeanteu          #+#    #+#             */
/*   Updated: 2018/07/26 12:48:16 by ljeanteu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"
#include "ft_btree_rb.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST(x) {fprintf(stderr, "%s (%s): %d %d %d %d %d\n", #x, \
		(x)->data,	\
		(x) == (x)->parent,	\
		(x) == (x)->left,	\
		(x) == (x)->right,	\
		(x)->right?(x)		\
		!= (x)->right->parent:0, (x)->left?(x) != (x)->left->parent:0);}

#define INSERT(a, b, c) btree_insert_data(a, b, c)

void	show(void *a)
{
	printf("%s \n", a);
}

void	good_show(void *a, int level, int is_first_elem)
{
	if (is_first_elem)
		printf("\n%d:", level);
	printf("\t%s", a);
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
	t_btree		*begin;
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
	btree_apply_prefix(begin, &show);
	printf("\n");
	btree_apply_infix(begin, &show);
	printf("\n");
	btree_apply_suffix(begin, &show);
	printf("\n\n");
	i = 1;
	while (i < argc)
	{
		result = btree_search_item(begin, argv[i], &cmpfunc);
		show(result);
		i += 2;
	}
	printf("\n");
	printf("%d \n", btree_level_count(begin));
	btree_apply_by_level(begin, &good_show);
	fflush(stdout);
	return (0);
}
