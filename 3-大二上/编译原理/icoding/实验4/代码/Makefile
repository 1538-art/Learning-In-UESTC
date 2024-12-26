all: lrparser.tab.c lex.yy.c ast.c main.c genllvm.c
	gcc -o genllvm lrparser.tab.c lex.yy.c ast.c genllvm.c main.c

lrparser.tab.c : lrparser.y
	bison -d lrparser.y

lex.yy.c : lrlex.l
	flex lrlex.l
	

