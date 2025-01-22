#include <stdio.h>

typedef enum {
    V4 = 0,
    V6 = 1
} myEnum;

typedef struct {
    myEnum e;
    char add[4];
} Ip4;

typedef struct {
   myEnum e;
   char* addr;
} Ip6;

int main() {
    
}
