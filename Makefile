CC=gcc
all:
	mkdir buildDir
	$(CC) -c -g interpret.c -o buildDir/intepret.o
	$(CC) -c -g main.c -o buildDir/main.o
	$(CC) -c -g libs/startswith.c -o buildDir/startswith.o
	$(CC) buildDir/main.o buildDir/intepret.o buildDir/startswith.o -o build
	rm -rf buildDir

windows:
	mkdir buildDir
	$(CC) -c -g interpret.c -o buildDir/intepret.o
	$(CC) -c -g main.c -o buildDir/main.o
	$(CC) -c -g libs/startswith.c -o buildDir/startswith.o
	$(CC) buildDir/main.o buildDir/intepret.o buildDir/startswith.o -o build.exe
	rmdir .\buildDir\ /s /q


run:
	./build -d