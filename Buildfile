var CC = gcc
-all
    echo hello
    $(CC) -v -a
    rm -rf build-bootstrapped/
    mkdir build-bootstrapped
