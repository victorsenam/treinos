#include<bits/stdc++.h>
#define MAX 215
using namespace std;
// n - Número de cavalos 
// m - Número de soldados
// k - Número de afinidades
// Indices do grafo:
// [0] é a source
// [1..n] são os cavalos
// [n+1..n+m] são os soldados
// [n+m+1] é o sumidouro
// Total de n+m+2 <= 2*max+2 = 202
// graph[u] me devolve (v, c(u,v));

typedef int num;
num anc[MAX], n, m, k;
vector< pair<num, num> > graph[MAX];

// Não precisa de parâmetros, sempre mesmo s e t
// Retorna o minf de 0 para n+m+1
num bfs()
{
    anc[0] = 0;
    for( int i = 1; i <= n + m + 1 ; i++ )
        anc[i] = -1;

    queue< pair<num, num> > toVisit;
    toVisit.push( make_pair(0, INT_MAX) );
    while( !toVisit.empty() )
    {
        num v = toVisit.front().first,
            f = toVisit.front().second; // Quanto flow chega no vértice
        toVisit.pop();
        if( v == n+m+1 ) return f;
        for( int i = 0; i < graph[v].size(); i++ )
        {
            num adj = graph[v][i].first,
                cos = graph[v][i].second;// Quanto flow passa na aresta
            if( anc[adj] < 0 && cos > 0 )
            {
                anc[adj] = v;
                toVisit.push( make_pair( adj, min(cos, f) ) );
            }
        }
    }
}

int main()
{
    int ct = 1;
    while( scanf("%d %d %d", &n, &m, &k) != EOF )
    {
        // Limpa a casa
        num flow = 0, minf;
        for( int i = 0; i < n+m+1; i++ )
            graph[i].clear();

        // Todos os soldados só podem montar em um cavalo
        for( int i = 1; i <= m; i++ )
        {
            graph[0].push_back( make_pair(n+i, 1) );
            graph[n+1].push_back( make_pair(0, 0 ));
        }

        // n inteiros, a capacidade de cada cavalo
        for( int i = 1; i <= n; i++ )
        {
            num c;
            scanf("%d", &c );
            graph[i].push_back( make_pair(n+m+1, c) );
            graph[n+m+1].push_back( make_pair(i, 0) );
        }

        for( int i = 0; i < k; i++ )
        {
            num c, s;
            scanf("%d %d", &c, &s);
            // cavalo soldado
            // fluxo deve ir de soldado para cavalos
            graph[n+s].push_back( make_pair(c, 1) );
            graph[c].push_back( make_pair(n+s, 0) );
        }

        for( minf = bfs(); anc[n+m+1] > 0; minf = bfs() )
        {
            // O vetor ancestral me dá um caminho pelo grafo residual
            // preciso percorrer o caminho e atualizer o grafo
            // Posso passar minf[n+m+1] pelo caminho em anc
            for(int i = n+m+1; i != 0 ; i = anc[i] )
            {
                num d = anc[i],
                    p = i;

                // Existe uma aresta d -> p em graph
                for( int i = 0; i < graph[d].size() ; i++)
                    if( graph[d][i].first == p )
                        graph[d][i] = make_pair( p, graph[d][i].second - minf );

                for( int i = 0; i < graph[p].size() ; i++)
                    if( graph[p][i].first == d )
                        graph[p][i] = make_pair( d, graph[p][i].second + minf );
            }
            flow += minf;
        }
        printf("Instancia %d\n%d\n",ct++, flow);
    }
}
