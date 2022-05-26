#include <stdio.h>
#include <stdlib.h>
palette[256*3];
main()
{
for (int i=0; i<256*3; i++)
    {
    printf("%d, ", random(255));
    if ((i & 3) == 0)
        printf("\n");
    }
}
