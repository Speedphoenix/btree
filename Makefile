NAME			=	libbtree.a
LIBNAME			=	btree

CC				=	gcc

AR				=	ar

ARFLAGS			=	rc

INDEXER			=	ranlib

WARNINGS		=	-Wall -Wextra								\
#					-Werror

SRDIRS			=	.

DEFAULTFLAGS	=	-O2 $(WARNINGS)

INCLUDEPFLAGS	=	-I.

CFLAGS			=	$(DEFAULTFLAGS) $(INCLUDEPFLAGS)

SRC				:=	basic_modifs.c								\
					basic_ops.c									\
					node_init.c									\
					tree_init.c									\
					iterate.c									\
					iterator_ops.c								\
					relative_ops.c								\
					rb_insert.c									\
					rb_destroy.c								\
					rb_remove.c

# $(wildcard $(addsuffix /*.cpp, $(SRDIRS)))

OBJ				:=	$(SRC:.c=.o)


LDLIBS			:=	-l$(LIBNAME)

LDFLAGS			:=	-L.

TSTINGLDLIBS	:=	

RM				=	/bin/rm -f

.PHONY: all clean fclean re

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)
	$(INDEXER) $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)
