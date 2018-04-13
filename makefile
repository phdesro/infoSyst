all: compiler

lex.yy.c: compiler.l
	./flex	compiler.l

compiler.tab.c: compiler.y
	~/bison/bin/bison -d compiler.y

compiler: compiler.tab.c lex.yy.c symtab/symbol.c symtab/symboltab.c
	gcc -o compiler lex.yy.c compiler.tab.c symtab/symbol.c symtab/symboltab.c libfl.a ~/bison/lib/liby.a

test: compiler
	./compiler < test.c

testsymbol: symtab/symbol.c symtab/symboltab.c symboltest
	gcc symtab/symbol.c symtab/symboltab.c -o symtab/
	symtab/symboltest
