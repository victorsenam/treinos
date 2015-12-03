#include <bits/stdc++.h>
#define MAX 1000005
using namespace std;
typedef unsigned long long num;
num maxPrime, in, primes[MAX];
char comp[MAX];
int ps;

void sieve( num limit )
{
    ps = 0;
    memset( comp, 0, sizeof comp );
    comp[0] = comp[1] = 1;
    for( int i = 2; i <= limit; i++ )
        if( !comp[i] )
        {
            primes[ps++] = i;
            for( int j = 2*i; j <= limit; j += i )
                comp[j] = 1;
        }
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> in;
    for( maxPrime = 0; maxPrime*maxPrime <= in; maxPrime++ );
    cout << maxPrime << endl;

    sieve( maxPrime );
    for( int i = ps-1; i >= 0; i-- )
        if( in%primes[i] == 0 )
        {
            cout << primes[i] << endl;
            break;
        }
}
