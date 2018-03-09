all: compiler
lex.yy.c: compiler.l
	./flex	compiler.l

compiler.tab.c: compiler.y
	/home/desroche/bison/bin/bison -d compiler.y

compiler: compiler.tab.c lex.yy.c
	gcc -o compiler lex.yy.c compiler.tab.c libfl.a /home/desroche/bison/lib/liby.a

test: compiler
	./compiler < test.c

