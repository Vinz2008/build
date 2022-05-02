var CC = gcc
-all
    echo hello
    $(CC) -v -a
    rm -rf build-bootstrapped/
    mkdir build-bootstrapped
	gcc -c -g interpret.c -o build-bootstrapped/intepret.o
	gcc -c -g main.c -o build-bootstrapped/main.o
	gcc -c -g libs/startswith.c -o build-bootstrapped/startswith.o
	gcc build-bootstrapped/main.o build-bootstrapped/intepret.o build-bootstrapped/startswith.o -o build-bootstrapp
