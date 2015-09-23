#include<bits/stdc++.h>
using namespace std;
typedef int num;
const int MN = 1000000;
char comp[MN];
num primes[MN], ps, n;

int main()
{
    n = 100000;
    printf("%d\n", n);
    comp[0]=comp[1]=1;
    for(int i=2; i < MN && ps < n; i++)
        if( !comp[i] )
        {
            printf("%d ", i);
            for(int j=2*i;j<MN;j+=i)
                comp[j] = 1;
        }
}
