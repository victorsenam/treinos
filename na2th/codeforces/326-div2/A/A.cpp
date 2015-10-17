#include<bits/stdc++.h>
using namespace std;
typedef int num;
typedef int node;
typedef int edge;

const int MN = 100001;
num n, a[MN], pri[MN], p[MN], seen[MN], ans;

bool priLess(int i, int j)
{ return pri[i] < pri[j]; }

int main()
{
    scanf("%d", &n);
    for(int i=0;i<n;i++)
        scanf("%d%d", a+i, pri+i), p[i] = i;

    sort(p,p+n,priLess);

    for(int i=0;i<n;i++)
    {
        num c = p[i];
        while( c < n && seen[c] == 0 )
        {
            seen[c] = 1;
            ans += a[c++]*pri[p[i]];
        }
    }

    printf("%d\n", ans);
}
