#ifndef INFOSYST_UTIL_H
#define INFOSYST_UTIL_H

#include "../symtab/symboltab.h"
#include "../memins/meminstr.h"

/**
 * Generate ASM for "Arithmetic Expressions".
 * Used to generate ADD, SUB, DIV, MUL, EQU, INF, INFE, SUP, SUPE, DIF
 * @param symbolTable
 * @param memInst
 * @param opCode
 */
void util_op	(SymbolTab * symbolTable, MemoireInstr * memInst, OpCode opCode);

/**
 * Copy file
 * @param from : location of source
 * @param to : location of destination
 */
void util_copy_file (char * from, char * to);

#endif //INFOSYST_UTIL_H
