all: compiler

lex.yy.c: compiler.l
	./flex	compiler.l

compiler.tab.c: compiler.y
	~/bison/bin/bison -d compiler.y

compiler: compiler.tab.c lex.yy.c symbol.c symboltab.c
	gcc -o compiler lex.yy.c compiler.tab.c symbol.c symboltab.c libfl.a ~/bison/lib/liby.a

test: compiler
	./compiler < programmeAAnalyser.c

testsymbol: symbol.c symboltab.c
	gcc symbol.c symboltab.c -o symboltest
	./symboltest
