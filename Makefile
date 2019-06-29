NAME			=	libbtree.a
LIBNAME			=	btree

TESTINGNAME		=	test.out

CC				=	gcc

AR				=	ar

ARFLAGS			=	rc

INDEXER			=	ranlib

WARNINGS		=	-Wall -Wextra								\
#					-Werror

SRDIRS			=	.

DEFAULTFLAGS	=	-O2 $(WARNINGS)

INCLUDEPFLAGS	=	-Itesting/ -I.

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

TESTINGSRC		:=	testing/main.c								\
					testing/main_checks.c						\
					testing/displays.c							\
					testing/btree_apply_by_level.c				\
					testing/saveHTML.c							\
					testing/check_remove.c

# $(wildcard $(addsuffix /*.cpp, $(SRDIRS)))

OBJ				:=	$(SRC:.c=.o)

TESTINGOBJ		:=	$(TESTINGSRC:.c=.o)

LDLIBS			:=	-l$(LIBNAME)

LDFLAGS			:=	-L.

TSTINGLDLIBS	:=	

RM				=	/bin/rm -f

.PHONY: all clean fclean re cleantest fcleantest retest dotests

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)
	$(INDEXER) $(NAME)

$(TESTINGNAME): $(NAME) $(TESTINGOBJ)
	$(CC) -o $(TESTINGNAME) $(TESTINGOBJ) $(LDFLAGS) $(LDLIBS)

dotests: $(TESTINGNAME)
	./$(TESTINGNAME)

all: $(NAME) $(TESTINGNAME)

cleantest:
	$(RM) $(TESTINGOBJ)

fcleantest: cleantest
	$(RM) $(TESTINGNAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean fcleantest $(NAME)

retest: re $(TESTINGNAME)
