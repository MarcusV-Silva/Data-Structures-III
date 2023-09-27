all: compile run 

compile1: 
	gcc -Wall -o programaTrab main.c funcionalidade1.c funcoesFornecidas.c  -g

compile2: 
	gcc -Wall -o programaTrab main.c funcionalidade2.c funcoesFornecidas.c -g

compile3: 
	gcc -Wall -o programaTrab main.c funcionalidade3.c funcoesFornecidas.c  -g

compile4: 
	gcc -Wall -o programaTrab main.c funcionalidade4.c funcoesFornecidas.c -g

compile:
	gcc -Wall -o programaTrab *.c -g
	
run: 
	./programaTrab

valgrind: 
	valgrind ./programaTrab

clean:
	rm programaTrab 