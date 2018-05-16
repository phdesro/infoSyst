#include "util_string.h"

String * new_String()	{
	String * tmp = malloc(sizeof(String));
	tmp->content = malloc(sizeof(char) * EXT);
	tmp->max = EXT;
	return tmp;
}

char * us_content(String * str)	{
	int str_len = strlen(str->content);

	// wrap the content into tmp
	char * tmp = malloc(sizeof(char) * (str_len));
	strcpy(tmp, str->content);

	// free the main content and give the result
	us_delete(str);

	return tmp;
};

void us_append(String * str, char character) {

	int str_len = strlen(str->content);

	// extend the string if content > capacity
	if(str_len >= str->max)   {
		str->max += EXT;
		char * tmp = malloc(sizeof(char) * (str->max));
		strcpy(tmp, str->content);
		free(str->content);
		str->content = tmp;
	}

	str->content[str_len] = character;
}

void us_delete(String * str) {
	free(str->content);
	free(str);
}