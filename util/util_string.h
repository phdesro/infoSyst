
#ifndef INFOSYST_UTIL_STRING_H
#define INFOSYST_UTIL_STRING_H

#include <stdlib.h>
#include <string.h>

#define EXT 10
typedef struct {
	int max;
	char* content;
} String;

String * new_String();

char * us_content(String * str);

void us_append(String * str, char character);

void us_delete(String * str);

#endif //INFOSYST_UTIL_STRING_H
