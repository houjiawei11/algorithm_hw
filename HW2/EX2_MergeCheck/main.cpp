#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "check.h"

#define MAX_LEN 255
#define LOOP 2000
#define LLEN 5000

int main()
{
    // A sample input
    // You can write your own test code.
    char A[] = "Cormen";
    char B[] = "Leiserson";
    char C[] = "CieLosrmeresonn";

    // Check correctness
    // In this case, the merge check should return false since the character order of A and B is wrong
    if (check(A, B, C) == 0)
        printf("PASS.\n");

    // Check complexity
    srand((unsigned int)time(NULL));
    char LA[LLEN];
    char LB[LLEN];
    char* LC = (char*) malloc (sizeof(char)*(LLEN*2-1));
    for (int i = 0; i < LLEN; i++)
    {
        // random character, in this simple case your check algorithm should return 1
        LC[2*i] = LA[i] = random()%26 + 'a';
        LC[2*i+1] = LB[i] = random()%26 + 'a';
    }
    LA[LLEN-1] = LB[LLEN-1] = LC[LLEN*2-2] = '\0';

    clock_t begin = clock();

    for (int i = 0; i < LOOP; i++)
    {
        check(A, B, C);
    }
    clock_t end = clock();
    printf("Time consuming for %d times: %f ms\n", LOOP, (double)(end-begin)*1000/CLOCKS_PER_SEC);

    free(LC);
    // Don't forget to call free() here if you malloc something in your test code
    // free(your_ptr);

    return 0;
}
