#include <cstdio>
#include <cstring>

using namespace std;

int main()
{
    char input[1000];
    int freq[90], i;
    memset(input, 0, 1000);
    while ( scanf("%[^\n]%*c", input) > 0 ) {
        memset(freq, 0, 90);
        for (i = 0; i < 1000 and input[i] != 0; i++) 
            freq[input[i] - 32] += 1;
        for ( i = 0; i < 90 ; i++ )
            if(freq[i] > 0 )
                printf("%d %d\n", i+32, freq[i]);
        memset(input, 0, 1000);

    }
}
