#include<bits/stdc++.h>
#define MP 200
#define MM 54
#define MC 54
using namespace std;
typedef int num;
typedef long long int ll;
typedef pair<pair<ll, int>, int> vert;
int ps, ms;
num x[MP], y[MP];
num p1[MM], p2[MM];
num pending[MP];
num t,m,c, q, p, anchor, pds;
vector<pair<ll, int> > graph[MC];
double dqc[MC], dcp[MC];
double bdist;
priority_queue<vert> pq;
ll visi[MP][MC];

long long djs()
{
    vert aux;
    pair<ll, int> adj;

    for (int i = 0; i < ps; i++)
        for (int j = 0; j < t; j++)
            visi[i][j] = LLONG_MAX;
    while(!pq.empty()) pq.pop();

    aux.first.first = 0;
    aux.first.first = t;
    aux.second = c+2*m;
    pq.push(aux);

    while (!pq.empty()) {
        aux = pq.top();
        pq.pop();

        printf("%lld %d %d\n", aux.first.first, aux.first.second, aux.second);
        
        if (aux.second == c+2*m+1) return aux.first.first;

        for (int i = 0; i < graph[aux.second].size(); i++) {
            adj = graph[aux.second][i];
            
            if (adj.first == 0ll && aux.first.second > 0) {
                if (adj.second == c+2*m+1) return aux.first.first;
                pq.push(make_pair(make_pair(aux.first.first, aux.first.second-1), adj.second));
            } else {
                if (adj.second == c+2*m+1) return aux.first.first + adj.first;
                pq.push(make_pair(make_pair(aux.first.first + adj.first, aux.first.second), adj.second));
            }
        }
    }
}

inline int cP(int a, int b, int c)
{
    return (x[a]*(y[b]-y[c]) +
            y[a]*(x[c]-x[b]) +
            x[b]*y[c] - x[c]*y[b]);
}

inline int sign(int x)
{
    if(x > 0) return 1;
    if(x == 0) return 0;
    return -1;
}
inline bool improperInt(int a,int b, int c, int d)
{
    return  (
        sign(cP(a,b,c))*sign(cP(a,b,d)) <= 0 &&
        sign(cP(c,d,a))*sign(cP(c,d,b)) <= 0
    );
}
inline long long pointDist(int a, int b)
{
    return (x[a]-x[b])*(x[a]-x[b]) + (y[a]-y[b])*(y[a]-y[b]);
}

inline bool grahamLess(int a, int b)
{
    int val = cP(anchor,a,b);
    if( val != 0 ) return val > 0;
    else return x[a] < x[b];
}

inline bool lexicalLess(int a, int b)
{
    if( x[a] == x[b] ) return y[a] < y[b];
    return x[a] < x[b];
}


int main()
{
    while( scanf("%d %d %d", &t, &m, &c) != EOF )
    {
        int x1,x2,y1,y2;
        ps = c; ms = 0;
        for( int i = 0; i < m; i++ )
        {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            x[ps] = x1; y[ps] = y1; p1[ms] = ps++;
            x[ps] = x2; y[ps] = y2; p2[ms++] = ps++;
        }
        for(int i = 0; i < c; i++)
        {
            scanf("%d %d", &x1, &y1);
            x[i] = x1; y[i] = y1;
        }
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        x[ps] = x1; y[ps] = y1; q = ps++;
        x[ps] = x2; y[ps] = y2; p = ps++;

        // Monta grafo dos teletransporetes
        for( int i = 0; i < c + 2*m + 3; i++)
            graph[i].clear();

        for(int i = 0; i < c; i++)
            for( int j = i+1; j < c; j++)
            {
                bool livre = true;
                for( int k = 0; livre && k < m; k++ )
                    livre = livre && !improperInt(i,j,p1[k],p2[k]);
                if( livre )
                {
                    graph[i].push_back( make_pair( 0, j ));
                    graph[j].push_back( make_pair( 0, i ));
                }
            }

        pds = ps;
        for(int i = 0; i < ps; ps++)
            pending[i] = i;

        while( pds > 0 )
        {
            anchor = pending[0];
            int ai = 0;
            for( int i = 1; i < pds; i++ )
                if( lexicalLess(pending[i], anchor) )
                {
                    anchor = pending[i];
                    ai = i;
                }
            graph[anchor].clear();
            swap(pending[pds-1], pending[ai]); pds--;
            sort(pending, pending+pds, grahamLess);
            for(int v = 0; v < pds; v++ )
            {
                graph[anchor].push_back( make_pair( pointDist(anchor, pending[v]), pending[v] ));
                // Se for parede, corta minha visão
                if( c < pending[v] && pending[v] < 2 + 2*m )
                {
                    int skipTo = pending[v]^1;
                    while( pending[v] != skipTo ) v++;
                }
            }
        }

        printf("%.1f\n", sqrt(djs()));
    }
}
