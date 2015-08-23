#include <cstdio>

using namespace std;

int main()
{
    int n, p, counter;
    bool prime;
    scanf("%d ", &counter);
    for(; counter > 0 ; counter--)
    {
        scanf("%d ", &p);
        prime = (p >= 2);
        for( n = 2 ; prime && n*n <= p ; n++ )
            if(p%n == 0) prime = false;

        if(prime)
            printf("%d eh primo\n", p);
        else
            printf("%d nao eh primo\n", p);
    }
}
