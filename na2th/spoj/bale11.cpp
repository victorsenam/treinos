#include<bits/stdc++.h>
#define MN 100002
using namespace std;
typedef int num;
num tree[MN], in[MN], p[MN], n, ans;

bool inLess(int a, int b)
{ return in[a] < in[b]; }

void insert( int p, num val )
{
    for(; p <= n; p += (p&-p) )
        tree[p] += val;
}

num count(int p)
{
    num sum = 0;
    for(; p > 0; p -= (p&-p) )
        sum += tree[p];
    return sum;
}

int main()
{
    scanf("%d", &n);
    for( int i = 1; i < n + 1; i++ )
    {
        scanf("%d", in+i);
        tree[i] = (i&-i);
        p[i-1] = i;
    }
    sort(p, p+n, inLess);
    for( int i = 0; i < n; i++ )
    {
        insert(p[i], -1);
        ans += count(p[i]);
    }
    printf("%d\n", ans);
}
