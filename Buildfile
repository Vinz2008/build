var CC = gcc
all:
    echo hello
    $(CC) -v
    rm -rf build-bootstrapped/
    mkdir build-bootstrapped
    $(CC) -c -g interpret.c -o build-bootstrapped/intepret.o
    $(CC) -c -g main.c -o build-bootstrapped/main.o
    $(CC) -c -g libs/startswith.c -o build-bootstrapped/startswith.o
    $(CC) build-bootstrapped/main.o build-bootstrapped/intepret.o build-bootstrapped/startswith.o -o build-bootstrapp
