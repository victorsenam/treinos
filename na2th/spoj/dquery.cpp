#include<bits/stdc++.h>
using namespace std;
typedef int num;
num in[30003], next[30002], tree[30002],
    last[1000003], ans[200002],
    n, q;
set< pair<pair<num,num>, num> > queries;

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

int main()
{
    for( int i = 0; i < 1000003 ; i++ )
        last[i] = -1;

    scanf("%d", &n);
    for( int i = 1; i < n+1; i++ )
    {
        scanf("%d", in+i);
        if( last[in[i]] == -1 )
        {
            insert(i, 1);
            last[in[i]] = i;
        }
        else
        {
            next[last[in[i]]] = i;
            last[in[i]]       = i;
        }
    }
    scanf("%d", &q);
    for( int k = 0; k < q; k++ )
    {
        num i, j;
        scanf("%d %d", &i, &j);
        queries.insert( make_pair(make_pair(i,j), k) );
    }
    num currI = 1;
    while( !queries.empty() )
    {
        while( currI < queries.begin()->first.first )
        {
            insert(currI, -1);
            if( next[currI] > 0 )
                insert(next[currI], 1);
            currI++;
        }
        ans[queries.begin()->second] = count(queries.begin()->first.second);
        queries.erase( queries.begin() );
    }
    for( int i = 0; i < q; i++ )
        printf("%d\n", ans[i]);
}
