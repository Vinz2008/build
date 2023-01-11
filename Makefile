CC=gcc
CFLAGS=-Wall -c -g

OBJS=\
libs/startswith.o \
interpret.o \
lexer.o \
main.o \

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
	rm -rf buildDir
	rm -f testsBin build
