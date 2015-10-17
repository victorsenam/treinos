#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long num;
typedef int node;
typedef int edge;

const int MN = 1000001;
char comp[MN];
num primes[MN], ps, n, ans;

int main()
{
    for(num i=2llu;i<MN;i++)
        if( !comp[i] )
        {
            primes[ps++] = i;
            if( primes[ps-1]*primes[ps-1] > 1000000000000llu ) break;
            for(num j=2llu*i;j<MN;j+=i)
                comp[j] = 1;
        }
    ans = 1llu;
    cin >> n;
    for(int i=0;i<ps;i++)
        if( n%primes[i] == 0 )
        {
            ans *= primes[i];
            while( n%primes[i] == 0 )
                n /= primes[i];
        }
    if( n > 1llu )
        ans *= n;
    cout << ans << endl;
}
