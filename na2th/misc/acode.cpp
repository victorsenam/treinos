#include <cstdio>
#include <cstring>

using namespace std;

int countComb(int i, char * input, int * poss)
{
    if( poss[i] == -1 )
    {
        if( input[i] == 0x30 )
        {
            poss[i] = 0;
            return 0;
        }

        if( input[i+1] == 0 || input[i] == 0 )
        {
            poss[i] = 1;
            return 1;
        }

        int num = 10*(input[i] - 0x30) + (input[i+1] - 0x30);
        if( num <= 26 )
        {
            poss[i] = countComb(i+2, input, poss);
            if( num%10 != 0 )
                poss[i] += countComb(i+1, input, poss);
        }
        else
            poss[i] = countComb(i+1, input, poss);
    }
    return poss[i];
}

int main()
{
    char input[5001];
    int poss[5042];
    while( scanf("%s", input ) > 0 )
    {
        if(input[0] == '0' && input[1] == 0)
            break;

        memset(poss, -1, sizeof(poss));

        printf("%d\n", countComb(0, input, poss));
        memset(input, 0, sizeof(input));
    }
}
