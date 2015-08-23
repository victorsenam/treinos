#include<bits/stdc++.h>
#define MV 5002
#define ME (2*5002*4999)
typedef int num;
typedef int node;
typedef int edge;
using namespace std;

int head[MV], rhad[MV], label[MV], order[MV], os, vs;
int to[ME], next[ME], es;
num iv, ie, cmps;

void add( node u, node v )
{
    to[es] = v; next[es] = head[u]; head[u] = es++;
    to[es] = u; next[es] = rhad[v]; rhad[v] = es++;
}

void findOrder( node u )
{
    label[u] = 1;
    for( edge e = rhad[u]; e >= 0; e = next[e] )
        if( label[to[e]] == -1 )
            findOrder(to[e]);
    order[os++] = u;
}

void dfs( node u, num l )
{
    label[u] = l;
    for( edge e = head[u]; e >= 0; e = next[e] )
        if( label[to[e]] == -1 )
            dfs( to[e], l );
}

void findStrong()
{
    os = 0;
    memset( label, -1, sizeof label );
    for( node u = 0; u < vs; u++ )
        if( label[u] == -1 )
            findOrder(u);
    memset( label, -1, sizeof label );
    cmps = 0;
    for( ; os > 0; os-- )
        if( label[order[os-1]] == -1 )
            dfs( order[os-1], cmps++ );
}

int main()
{
    while( scanf("%d %d", &iv, &ie) && iv  )
    {
        memset(head, -1, sizeof head);
        memset(rhad, -1, sizeof rhad);
        es = 0; vs = iv;
        while( ie-- > 0 )
        {
            node u, v;
            scanf("%d %d", &u, &v);
            u--; v--;
            add(u,v);
        }
        findStrong();
        for( node u = 0; u < vs; u++ )
            if( 0 <= label[u] && label[u] < cmps )
            {
                node v = u;
                num c = label[u];
                bool sink = true;
                while( sink && v < vs )
                {
                    for( edge e = head[v]; sink && e >=0 ; e = next[e])
                        sink = ( label[to[e]] == c );
                    for(v++; v < vs && label[v] != c; v++);
                }
                if( sink )
                {
                    for( v = 0; v < vs; v++ )
                        if( label[v] == c )
                            label[v] += cmps;
                }
                else
                    for( v = 0; v < vs; v++ )
                        if( label[v] == c )
                            label[v] = -1;
            }
        for( node u = 0; u < vs; u++ )
            if( label[u] > 0 )
                printf("%d ", u+1 );
        printf("\n");
    }
}
