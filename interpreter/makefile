CC := gcc
DIR_SYMTAB := symtab
DIR_MEMINS := memins

all: exec

lex.yy.c: interpreter.l
	../flex	interpreter.l

interpreter.tab.c: interpreter.y
	~/bison/bin/bison -d -v interpreter.y

exec: interpreter.tab.c lex.yy.c
	$(CC) -o interpreter lex.yy.c interpreter.tab.c ../libfl.a ~/bison/lib/liby.a
	./interpreter < test.asm

clean:
	echo "NOT IMPLEMENTED ======"


	
