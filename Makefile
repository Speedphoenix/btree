NAME			=	btree
LIBNAME			=	libbtree.a

USERINCLUDE		=	btree.h

CC				=	gcc

AR				=	ar

ARFLAGS			=	rc

INDEXER			=	ranlib

INSTALL			=	install

# PREFIX is an environment variable, but if it is not set, then set default value
ifeq ($(PREFIX),)
	PREFIX		:= /usr
endif

LIBDEST			=	$(DESTDIR)$(PREFIX)/lib/
INCLUDEDEST		=	$(DESTDIR)$(PREFIX)/include/

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

LDFLAGS			:=	-L.

RM				=	/bin/rm -f

.PHONY: all clean fclean re $(NAME) install uninstall

$(NAME): $(LIBNAME)

$(LIBNAME): $(OBJ)
	$(AR) $(ARFLAGS) $(LIBNAME) $(OBJ)
	$(INDEXER) $(LIBNAME)

all: $(NAME)

installmv: $(LIBNAME)
	$(INSTALL) -d $(LIBDEST)
	$(INSTALL) -m 644 $(LIBNAME) $(LIBDEST)
	$(INSTALL) -d $(INCLUDEDEST)
	$(INSTALL) -m 644 $(USERINCLUDE) $(INCLUDEDEST)

install: | installmv fclean

uninstall:
	$(RM) $(LIBDEST)$(LIBNAME)
	$(RM) $(INCLUDEDEST)$(USERINCLUDE)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(LIBNAME)

re: fclean $(NAME)
