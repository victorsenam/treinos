#include<bits/stdc++.h>
#define MV 1000004
typedef int num;
num n,m, ans;

struct UnionFind
{
    num us, id[MV], sz[MV], comp;
    void set( int i )
    {
        us = i; comp = i;
        for( int i  = 0; i < us; i++ )
        {
            id[i] = i;
            sz[i] = 1;
        }
    }
    num find( int p )
    {
        id[p] = (id[p]==p) ? p : find( id[p] );
        return id[p];
    }
    bool connected(int u, int v)
    { return find(u) == find(v); }
    void unite( int u, int v)
    {
        u = find(u); v = find(v);
        if( u == v ) return;
        comp--;
        if( sz[u] < sz[v] )
        {
            id[u] = v;
            sz[v] += sz[u];
        }
        else
        {
            id[v] = u;
            sz[u] += sz[v];
        }
    }
} UF;

int main()
{
    char in;
    scanf("%d %d", &n, &m);
    UF.set( n*m );
    for( int i = 0; i < n; i++ )
    {
        for( int j = 0; j < m; j++ )
        {
            scanf("%c", &in);
            switch( in )
            {
                case 'N':
                    UF.unite(i*m+j, (i-1)*m + j);
                    break;
                case 'S':
                    UF.unite(i*m + j, (i+1)*m + j);
                    break;
                case 'E':
                    UF.unite(i*m + j, i*m + j + 1);
                    break;
                case 'W':
                    UF.unite(i*m + j, i*m + j - 1);
                    break;
                default:
                    j--;
            }
        }
    }
    printf("%d\n", UF.comp);
}
