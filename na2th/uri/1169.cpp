#include <cstdio>
#include <algorithm>

using namespace std;

unsigned long long twoFact( int n )
{
    if( n == 0 ) return 1u;
    else return 2u*twoFact(n-1);
}

int main()
{
    int input, n;
    unsigned long long output;
    scanf("%d", &n);
    for( ; n > 0 ; n--) {
        scanf("%d", &input);
        output = twoFact(input);
        printf("%llu\n", output/12);
    }
}
