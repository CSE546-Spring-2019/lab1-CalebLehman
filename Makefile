# makefile for count.c

SRCDIR=src
BUILDDIR=build

CC=gcc
CFLAGS=-g -Wall

DEPS=$(SRCDIR)/defs.h $(SRCDIR)/kmp.h $(SRCDIR)/naive.h
OBJS=$(BUILDDIR)/count.o $(BUILDDIR)/kmp.o $(BUILDDIR)/naive.o

all: count

naive: CFLAGS += -DNAIVE
naive: count

count: $(OBJS)
	$(CC) $(CFLAGS) -o $(BUILDDIR)/count $(OBJS)

$(OBJS): $(DEPS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BUILDDIR)/count
	rm -f $(BUILDDIR)/*.o
