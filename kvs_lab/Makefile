SRCS = main.c
LIBSRCS = open.c close.c put.c get.c 
TARG = kvs_static
TARG_DYNAMIC = kvs_dynamic

CC = gcc
OPTS = -Wall -g
LIBS = -L. -lkvs

OBJS = $(SRCS:.c=.o)
LOBJS = $(LIBSRCS:.c=.o)
LARS = libkvs.a
LDSO = libkvs.so

all: static dynamic

# Static target
static: $(TARG)

$(TARG): $(OBJS) $(LARS)
	$(CC) -o $(TARG) $(OBJS) $(LIBS) -static

$(LARS): $(LOBJS)
	ar rs $(LARS) $(LOBJS)

# Shared library for dynamic target
$(LDSO): $(LOBJS)
	$(CC) -shared -fPIC -o $(LDSO) $(LOBJS)

# Dynamic target
dynamic: $(TARG_DYNAMIC)

$(TARG_DYNAMIC): $(OBJS) $(LDSO)
	$(CC) -o $(TARG_DYNAMIC) $(OBJS) -L. -lkvs

%.o: %.c
	$(CC) $(OPTS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LOBJS) $(LARS) $(LDSO) $(TARG) $(TARG_DYNAMIC)

