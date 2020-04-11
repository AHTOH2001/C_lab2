all: build run clean
build: MainFile.c lab2z1v18.c lab2z2v18.c
	gcc -Wall -O0 -g3 -DDEBUG -pedantic-errors -std=c89 MainFile.c lab2z1v18.c lab2z2v18.c -o programm
	
run: programm.exe
	./programm.exe
	
clean: 
	rm -rf *.o programm