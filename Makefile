CC=gcc
CFLAGS=-Wall -c -g

SRCS := $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
all: build

build: $(OBJS)
	$(CC) -o $@ $^

%.o:%.c
	$(CC) $(CFLAGS) -o $@ $^

run:
	./build -d

install:
	cp build /usr/bin

clean:
	rm -rf buildDir testsBin build *.o
