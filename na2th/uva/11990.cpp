#include<bits/stdc++.h>
#define MN 200002
using namespace std;
typedef int num;
num treeA[MN], treeB[MN], in[MN], p[MN], n, m;
bool inLess(int a, int b)
{ return in[a] < in[b]; }

void insert( int * tree, int p, num val )
{
    for(; p <= n; p += (p&-p) )
        tree[p] += val;
}
num count( int * tree, int p )
{
    num sum = 0;
    for(; p > 0; p -= (p&-p) )
        sum += tree[p];
    return sum;
}
num freq( int * tree, int p )
{
    num ans = tree[p]; int goal;
    if( p == 0 ) return 0;
    for(goal = p-(p&-p), p--; p != goal; p -= (p&-p) )
        ans -= tree[p];
    return ans;
}

int main()
{
    while( scanf(" %d %d", &n, &m) != EOF )
    {
        for( int i = 1; i < n+1; i++ )
        {
            scanf("%d", in+i);
            p[i-1] = i;
            treeA[i] = (i&-i);
            treeB[i] = 0;
        }
        sort(p, p+n, inLess);
        for( int i = 0; i < n; i++ )
        {
            insert(treeA, p[i], -1);
            insert(treeB, i+1, count(treeA, p[i]));
            printf("%d : %d\n",i+1, count(treeA, p[i]));
        }
        for( int i = 0; i < m; i++ )
        {
            num aux, val; scanf("%d", &aux);
            printf("%d\n", count(treeB, n));
            val = freq(treeB, aux);
            printf("[%d][%d]",aux, val);
            insert(treeB, aux, -val);
        }
    }
}
