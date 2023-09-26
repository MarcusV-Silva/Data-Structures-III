all: compile run 

compile1: run
	gcc -Wall -o programaTrab main.c funcionalidade1.c funcoesFornecidas.c -g

compile:
	gcc -Wall -o programaTrab *.c -g
	
run: 
	./programaTrab

valgrind:
	valgrind ./programaTrab

clean:
	rm programaTrab 