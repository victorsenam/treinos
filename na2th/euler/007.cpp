#include <bits/stdc++.h>
#define MAX 10000000
using namespace std;
typedef unsigned long long num;
num primes[MAX], in;
int ps;
char comp[MAX];

num sieve(int goal)
{
    int limit = MAX;
    memset(comp, 0, sizeof comp);
    comp[0] = comp[1] = 1;
    ps = 0;
    for( int i = 2; i <= limit; i++ )
        if( !comp[i] )
        {
            primes[ps++] = i;
            if( ps == goal )
                return i;
            for( int j = 2*i; j<= limit; j+=i )
                comp[j] = 1;
        }
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> in;
    cout << sieve(in) << endl;
}
