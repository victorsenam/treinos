#include <bits/stdc++.h>
using namespace std;
typedef int num;

num k,n,w;

int main()
{
    while( scanf("%d %d %d", &k, &n, &w) > 0 )
    {
        num cost = k*((w*(w+1))/2);
        printf("%d\n", max(cost-n, 0));
    }
}
