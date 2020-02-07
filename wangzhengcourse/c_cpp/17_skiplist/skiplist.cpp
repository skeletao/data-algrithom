#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MAX_LEVEL 15

void random_init(void)
{
    static bool done = false;

    if (done) return;

    srand(time(NULL));
    done = true;
}

int random_level(void)
{
    int level = 1;
    int i = 0;

    random_init();

    for(i = 1; i< MAX_LEVEL; i++)
    {
        if (rand()%2 == 1) level++;
    }
    return level;
}

void random_level_test(void)
{
    printf("random level %d\r\n", random_level());
    printf("random level %d\r\n", random_level());
    printf("random level %d\r\n", random_level());
    printf("random level %d\r\n", random_level());
    printf("random level %d\r\n", random_level());
}

int main(void)
{
    random_level_test();
    return 0;
}