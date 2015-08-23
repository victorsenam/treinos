#include<bits/stdc++.h>
#define MN 30002
#define MQ 200002
using namespace std;
typedef int num;

num in[MN], tree[MN], toRemove[MN], tri, n, q;
num ans[MQ], lb[MQ], ub[MQ], f[MQ], queries[MQ];

void insert( int p, num val )
{
    for(; p <= n; p += (p&-p) )
        tree[p] += val;
}

num count( int p )
{
    num sum = 0;
    for(; p > 0; p -= (p&-p) )
        sum += tree[p];
    return sum;
}

bool qLess( int a, int b )
{ return f[a] < f[b]; }

bool inLess( int a, int b )
{ return in[a] < in[b]; }

int main()
{
    scanf("%d", &n);
    for( int i = 1; i < n+1; i++ )
    {
        scanf("%d", in+i);
        tree[i] = 1*(i&-i); // seta BIT pra 1
        toRemove[i-1] = i;
    }
    sort( toRemove, toRemove+n, inLess );
    scanf("%d", &q);
    for( int i = 0; i < q; i++ )
    {
        scanf("%d %d %d", lb+i, ub+i, f+i);
        queries[i] = i;
    }
    sort(queries, queries+q, qLess);
    for( int i = 0; i < q; i++ )
    {
        while( tri < n && in[toRemove[tri]] <= f[queries[i]] )
            insert(toRemove[tri++], -1);
        ans[queries[i]] = count(ub[queries[i]]) - count(lb[queries[i]]-1);
    }
    for( int i = 0; i < q; i++ )
        printf("%d\n", ans[i]);
}
