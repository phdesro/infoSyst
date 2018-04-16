all: compiler

lex.yy.c: compiler.l
	./flex	compiler.l

compiler.tab.c: compiler.y
	~/bison/bin/bison -d compiler.y

compiler: compiler.tab.c lex.yy.c symtab/symbol.c symtab/symboltab.c memins/instruction.c memins/meminstr.c memins/mitest.c memins/opcode.c
	gcc -o compiler lex.yy.c compiler.tab.c symtab/symbol.c symtab/symboltab.c memins/opcode.c memins/instruction.c memins/meminstr.c libfl.a ~/bison/lib/liby.a

test: compiler
	./compiler < test.c

testsymbol: symtab/symbol.c symtab/symboltab.c 
	gcc symtab/symbol.c symtab/symboltab.c -o symtab/symtest
	symtab/symboltest

testmemoire: memins/instruction.c memins/meminstr.c memins/mitest.c memins/opcode.c
	gcc memins/opcode.c memins/instruction.c memins/meminstr.c memins/mitest.c -o memins/mitest
	memins/mitest
	
