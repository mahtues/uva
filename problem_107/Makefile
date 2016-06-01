CC=gcc
CFLAGS=-O2 -pipe -ansi -DONLINE_JUDGE
LDFLAGS=-lm -lcrypt

all: problem test

problem: problem.c

test:
	time cat input | ./problem
