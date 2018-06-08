CC := gcc
DIR_SYMTAB := symtab
DIR_MEMINS := memins

all: compiler

lex.yy.c: compiler.l
	./flex	compiler.l

compiler.tab.c: compiler.y
	~/bison/bin/bison -d -v compiler.y

compiler: compiler.tab.c lex.yy.c symtab/symbol.c symtab/symboltab.c memins/instruction.c memins/meminstr.c memins/opcode.c util/util.c util/util_string.c
	$(CC) -std=c99 -o compiler lex.yy.c compiler.tab.c symtab/symbol.c symtab/symboltab.c memins/opcode.c util/util.c util/util_string.c memins/instruction.c memins/meminstr.c libfl.a ~/bison/lib/liby.a

test: compiler
	./compiler < test.c

test.symtab: $(DIR_SYMTAB)/symbol.c $(DIR_SYMTAB)/symboltab.c $(DIR_SYMTAB)/symtab.test.c
	$(CC) $(DIR_SYMTAB)/symbol.c $(DIR_SYMTAB)/symboltab.c $(DIR_SYMTAB)/symtab.test.c -o $(DIR_SYMTAB)/testsymtab
	$(DIR_SYMTAB)/testsymtab

test.memins: $(DIR_MEMINS)/instruction.c $(DIR_MEMINS)/meminstr.c $(DIR_MEMINS)/memins.test.c $(DIR_MEMINS)/opcode.c
	$(CC) $(DIR_MEMINS)/opcode.c $(DIR_MEMINS)/instruction.c $(DIR_MEMINS)/meminstr.c $(DIR_MEMINS)/memins.test.c -o $(DIR_MEMINS)/testmemins
	$(DIR_MEMINS)/testmemins

exec:
	interpreter/interpreter < interpreter/test.asm

clean:
	rm -rf compiler compiler.output compiler.tab.* lex.yy.c
	echo "DELETE UTEST OF SYMBOL TABLE ======"
	rm -rf symtab/testsymtab
	echo "DELETE UTEST OF INSTRUCTION MEMORY ======"
	rm -rf memins/testmemins


	
