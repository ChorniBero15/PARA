#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// 0100 0111
// 00000100


// 1111 0000
// 1111 1111

// 0-9
// a b c d e f


// 0x0
int read_first_4_bits(char byte) {
    return (byte >> 4) & 0x0f;
}

int read_last_4_bits(char byte) {
    return byte & 0x0F;
}
// ptr      |pr | ptr + 2


// compressed_string_ptr + 1 + 0
//                      
// 00010010 | a | 00100011 | b | c | 00010001 | x = "aabcbcbcx"




// 0001 = 1
// 
// 00000000 | 00010001 | x = "x" 

void Decompress(char **data) {
    //
}

void Test1()
{
    printf("Test1: ");
    char *expectValue = "aabcbcbcx";
    char *data = malloc(8);
    char *ptr = data;

    // 00010010|a|00100011|b|c|00010001|x
    *ptr = (1 << 4) + (1 << 1); // 00010010
    ptr++;
    *ptr = 'a';
    ptr++;
    *ptr = (1 << 5) + (1 << 1) + 1; // 00100011
    ptr++;
    *ptr = 'b';
    ptr++;
    *ptr = 'c';
    ptr++;
    *ptr = (1 << 4) + 1; // 00010001
    ptr++;
    *ptr = 'x';
    ptr++;
    *ptr = '\0';

    Decompress(&data);

    if (strcmp(expectValue, data) == 0)
    {
        printf("PASSED\n");
    }
    else
    {
        printf("FAILED after decompress: %s expected: %s\n", data, expectValue);
    }
    free(data);
}

void Test2()
{
    printf("Test2: ");
    char *expectValue = "yfoofoobar";
    char *data = malloc(11);
    char *ptr = data;

    // 00010001|y|00110010|f|o|o|00110001|b|a|r
    *ptr = (1 << 4) + 1; // 00010001
    ptr++;
    *ptr = 'y';
    ptr++;
    *ptr = (1 << 5) + (1 << 4) + (1 << 1); // 00110010
    ptr++;
    *ptr = 'f';
    ptr++;
    *ptr = 'o';
    ptr++;
    *ptr = 'o';
    ptr++;
    *ptr = (1 << 5) + (1 << 4) + 1; // 00110001
    ptr++;
    *ptr = 'b';
    ptr++;
    *ptr = 'a';
    ptr++;
    *ptr = 'r';
    ptr++;
    *ptr = '\0';

    Decompress(&data);

    if (strcmp(expectValue, data) == 0)
    {
        printf("PASSED\n");
    }
    else
    {
        printf("FAILED after decompress: %s expected: %s\n", data, expectValue);
    }
    free(data);
}

void Test3()
{
    printf("Test3: ");
    char *expectValue = "abcdefghfoofoo";
    char *data = malloc(14);
    char *ptr = data;

    // 10000001|a|b|c|d|e|f|g|h|00110010|f|o|o
    *ptr = (1 << 7) + 1; // 10000001
    ptr++;
    *ptr = 'a';
    ptr++;
    *ptr = 'b';
    ptr++;
    *ptr = 'c';
    ptr++;
    *ptr = 'd';
    ptr++;
    *ptr = 'e';
    ptr++;
    *ptr = 'f';
    ptr++;
    *ptr = 'g';
    ptr++;
    *ptr = 'h';
    ptr++;
    *ptr = (1 << 5) + (1 << 4) + (1 << 1); // 00110010
    ptr++;
    *ptr = 'f';
    ptr++;
    *ptr = 'o';
    ptr++;
    *ptr = 'o';
    ptr++;
    *ptr = '\0';

    Decompress(&data);

    if (strcmp(expectValue, data) == 0)
    {
        printf("PASSED\n");
    }
    else
    {
        printf("FAILED after decompress: %s expected: %s\n", data, expectValue);
    }
    free(data);
}

int main()
{
    Test1();
    Test2();
    Test3();
    return 0;
}
