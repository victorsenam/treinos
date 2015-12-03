#include <bits/stdc++.h>
using namespace std;
typedef int num;
const int N = 3e4+1;
const int M = 1e4+1;
num d[N], tot;

int main()
{
    for(int i=0;i<N; d[i]++,i++)
        for(int j=2; j*j<=i; j++)
            if(!(i%j)) d[i] += j + i/j;
    for(int i=2;i<M;i++)
        if(d[d[i]] == i && d[i] != i)
            tot += i;
    printf("%d\n", tot);
}
