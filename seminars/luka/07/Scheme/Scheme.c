
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

char *ConcatAll(nodeType *list) {
    nodeType t = *list;

    if(t == List) {
        list++;
        nodeType** subLists = (nodeType**)list;
        char* str1 = ConcatAll(subLists[0]);
        char* str2 = ConcatAll(subLists[1]);

        char* ans = malloc(strlen(str1) + strlen(str2) + 1);
        strcpy(ans, str1);
        strcat(ans, str2);

        free(str1);
        free(str2);

        return ans;
        
    } else if(t == String) {
        char* ans = (char*) ++list;
        return strdup(ans);
    } else {
        return strdup("\0");
    }
}

int main() {
    nodeType *stringNodes[32] = {};
    nodeType *intNodes   [32] = {};
    nodeType *listNodes  [32] = {};

    nodeType  nilNode = Nil;


    for (int i = 0; i < 32; i++) {
        char some_string[32] = {};

        sprintf(some_string, "test%d", i);

        
        nodeType *ptr = malloc(sizeof(nodeType) + strlen(some_string) + 1);

        *ptr = String;

        strcpy((char *)(ptr + 1), some_string);
        stringNodes[i] = ptr;
    }

    for (int i = 0; i < 32; i++) {
        
        nodeType *ptr = malloc(sizeof(nodeType) + sizeof(int));
        *ptr = Integer;

        memcpy(ptr + 1, &i, sizeof(int));

        intNodes[i] = ptr;
    }


    for (int i = 0; i < 32; i++) {
        
        nodeType *ptr = malloc(sizeof(nodeType) + 2 * sizeof(void *));
        *ptr = List;
        
        // set both pointers to nil

        ((nodeType **) (ptr + 1))[0] = &nilNode;
        ((nodeType **) (ptr + 1))[1] = &nilNode; 
        
        listNodes[i] = ptr;
    }

    for (int i = 0; i < 31; i++) {
        // connect all lists to eachother
        ((nodeType **) (listNodes[i] + 1))[1] = listNodes[i + 1]; 

        // even lists point to strings, odds point to ints
        if ( i % 2 == 0) {
            ((nodeType **) (listNodes[i] + 1))[0] = stringNodes[i]; 
        } else {
            ((nodeType **) (listNodes[i] + 1))[0] = intNodes[i]; 
        }
    }

    printf("%s\n", ConcatAll(listNodes[0]));
}