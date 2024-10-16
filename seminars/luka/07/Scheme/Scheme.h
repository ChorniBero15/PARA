
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum
{
	Integer,
	String,
	List,
	Nil
} nodeType;

char *ConcatAll(nodeType *list);
