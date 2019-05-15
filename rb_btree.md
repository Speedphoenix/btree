```c
enum	e_rb_color
{
	RB_BLACK,
	RB_RED
};

typedef struct			s_rb_node
{
	struct s_rb_node	*parent
	struct s_rb_node	*left;
	struct s_rb_node	*right;
	void				*data;
	enum e_rb_color		color;
}						t_rb_node;
```
### Example:
```
				7
		3				11
	1		5		9		13
  0	  2	  4	  6	  8	  10  12  14
```
### Rotation example (right):
|  Before   |    After   |
|:---------:|:----------:|
|`     |   `|`    |     `|
|`     3   `|`    1     `|
|`  1     5`|` 0     3  `|
|`0   2    `|`     2   5`|

## Properties
1. Nodes are Red or Black
2. Root is Black
3. All Leaves/NULL are Black
4. If a Node is Red, both Children are Black
5. Every path from the Root to NULL leaves contains the same amount of Black nodes
>	New Nodes are Red by default

## When inserting a node there are 4 cases:
1. The New node is the root
>	Paint the new node Black
2. The New node has a Black parent
>	Nothing, everything works fine
3. The Parent and Uncle are Red
>	Paint the Parent and Uncle Black, and the Grandparent red
>	Then call the case check + repair function again for the Grandparent in case it messed things up
4. The Parent is Red and the Uncle is Black
>	First make sure the New node is not on the 'inside' of the tree under the Grandparent ('inside' would be `G->left->right` or `G->right->left`)
>	>	If it is inside you can correct that by rotating the parent so that the New node becomes right under the Grandparent, and you can now use the node that used to be the Parent as the 'New node'
>	Rotate the Grandparent so that the Parent takes his place, paint the old Grandparent Red and the old Parent black (swap their colors)
>	Now the New node should be on the same level as the old Grandparent


## When removing a Node
1. If the Node has 2 non-leaf children
	* Take the inner-most node of it's sub trees.
	* Then copy the value of that node to replace the one we have to delete.
	* Then call the remove function recursively for the downstream node that now has to be deleted
>	>	Careful not to delete the downstream node's value when calling the function again
2. If the Node is Red
	* Replace it with its child (can only be a NULL/Leaf now because of property 5)
3. If the Node is Black and its child is Red
	* Replace it with its child
	* Paint the child Black
4. If the node is Black and its children too (children are therefore leaves)
	* First replace it with a child (leaf).
	1. If this New Leaf is the root we're done
	2. 
		1. This New leaf

https://en.wikipedia.org/wiki/Red%E2%80%93black_tree#Removal

We begin by replacing M with its child C. We will relabel this child C (in its new position) N, and its sibling (its new parent's other child) S. (S was previously the sibling of M.) In the diagrams below, we will also use P for N's new parent (M's old parent), SL for S's left child, and SR for S's right child (S cannot be a leaf because if M and C were black, then P's one subtree which included M counted two black-height and thus P's other subtree which includes S must also count two black-height, which cannot be the case if S is a leaf node).







