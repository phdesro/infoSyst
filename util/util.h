#ifndef INFOSYST_UTIL_H
#define INFOSYST_UTIL_H

#include "../symtab/symboltab.h"
#include "../memins/meminstr.h"

void util_cond	(SymbolTab * symbolTable, MemoireInstr * memInst, OpCode opCode);

void util_op	(SymbolTab * symbolTable, MemoireInstr * memInst, OpCode opCode);

#endif //INFOSYST_UTIL_H
