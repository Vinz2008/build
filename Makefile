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

install:
	cp build /usr/bin


test:
	make build-test
	
build-test:
	@mkdir buildDir
	@$(CC) -c -g interpret.c -o buildDir/intepret.o
	@$(CC) -c -g libs/startswith.c -o buildDir/startswith.o
	@$(CC) -c -g tests/test.c -o buildDir/test.o
	@$(CC) buildDir/intepret.o buildDir/startswith.o buildDir/test.o -o testsBin
	@rm -rf buildDir
	@./testsBin

clean:
	rm -rf buildDir
	rm -rf build-bootstrapped
	rm -f testsBin build
