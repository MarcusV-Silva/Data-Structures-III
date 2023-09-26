all: compile run valgrind

compile:
	gcc -Wall -o programaTrab *.c -g
	
run: 
	./programaTrab

valgrind:
	valgrind ./programaTrab

clean:
	rm programaTrab 