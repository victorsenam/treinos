#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
    int input[3], sorted[3], i;

    for (i = 0; i < 3; i++){
        scanf("%d", input+i);
        sorted[i] = input[i];
    }
    sort(sorted, sorted+3);


    for( i = 0 ; i < 3 ; i++)
        printf("%d\n", sorted[i]);
    printf("\n");

    for( i = 0 ; i < 3 ; i++)
        printf("%d\n", input[i]);

    return 0;
}
