CC=gcc
CFLAGS= -O2 -Werror -std=gnu99 
SOURCES = table.c rf.c cargs.c reader.c dt.c column.c tree.c confmatrix.c

all: rf

rf: table.c rf.c cargs.c reader.c dt.c column.c tree.c confmatrix.c