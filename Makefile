parser: main.c lex.l syntax.y symboltable.c semantics.c
	bison -d -v syntax.y
	flex lex.l
	gcc main.c syntax.tab.c symboltable.c semantics.c -lfl -ll -o parser
.PHONY: clean
clean :
	rm -rf lex.yy.c
	rm -rf parser
	rm -rf syntax.tab.c
	rm -rf syntax.tab.h

