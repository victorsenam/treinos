#include<bits/stdc++.h>
#define MP 200
#define EPS 1e-9
using namespace std;
typedef int num;
typedef int point;

num x[MP], y[MP];
point pend[MP], anchor, doc, por;
int ps, pds;
num t, m, c;

long long int d[MP];
int anc[MP];
vector< pair<int, long long> > adj[MP];
typedef pair< pair<long long, int>, point> state;

inline int cP(point a, point b, point c)
{
    return x[a]*(y[b]-y[c]) +
           y[a]*(x[c]-x[b]) +
           x[b]*y[c] - x[c]*y[b];
}

inline num sign( num x )
{
    if( x > 0  ) return 1;
    if( x == 0 ) return 0;
    return -1;
}

inline long long dist(point a, point b)
{
    return (x[a]-x[b])*(x[a]-x[b]) + (y[a]-y[b])*(y[a]-y[b]);
}

inline bool properInt( point a, point b, point c, point d )
{
    return ( sign(cP(a,b,c))*sign(cP(a,b,d)) < 0 &&
             sign(cP(c,d,a))*sign(cP(c,d,b)) < 0);
}

inline bool improperInt(point a,point b, point c, point d)
{
    if( properInt(a,b,c,d) ) return true;
    if( fabs(sqrt(dist(a,b)) - sqrt(dist(a,c)) - sqrt(dist(c,b))) < EPS ) return true;
    if( fabs(sqrt(dist(a,b)) - sqrt(dist(a,d)) - sqrt(dist(d,b))) < EPS ) return true;
    if( fabs(sqrt(dist(c,d)) - sqrt(dist(c,a)) - sqrt(dist(a,d))) < EPS ) return true;
    if( fabs(sqrt(dist(c,d)) - sqrt(dist(c,b)) - sqrt(dist(b,d))) < EPS ) return true;
    return false;
}

inline bool lexicalLess(point a,point b)
{
    if( x[a] == x[b] ) return y[a] < y[b];
    return x[a] < x[b];
}

inline bool grahamLess(point a,point b)
{
    num val = cP(anchor, a, b);
    if( !val ) return lexicalLess(a, b);
    return val > 0;
}

void connect(point a, point b)
{
    long long d = dist( a, b );
    adj[a].push_back( make_pair(b, d) );
    adj[b].push_back( make_pair(a, d) );
}

void djs(int s)
{
    for( int i = 0; i < ps; i++ )
        d[i] = LLONG_MAX;
    priority_queue<state, vector<state>, greater<state> > Q;
    d[s] = 0;
    Q.push( make_pair(make_pair(0LL, t),s) );
    while( !Q.empty() )
    {
        point     v  = Q.top().second;
        long long dv = Q.top().first.first;
        int       tr = Q.top().first.second;
        Q.pop();
        if( dv == d[v] )
        {
            for( int i = 0; i < adj[v].size(); i++ )
            {
                point     u = adj[v][i].first;
                long long w = adj[v][i].second;
                if( w > 0 )
                {
                    d[u] = min( d[u], d[v] + w );
                    Q.push( make_pair(make_pair( d[v] + w, tr ), u) );
                }
                else if ( tr > 0 )
                {
                    d[u] = min( d[u], d[v] );
                    Q.push( make_pair(make_pair( d[v], tr-1), u) );
                }
            }
        }
    }
}

int main()
{
    while( scanf("%d %d %d", &t, &m, &c) != EOF )
    {
        int x1,x2,y1,y2;
        // Primeiro endereço par >= c
        pds = 0;
        ps = c + c%2;
        for( int i = 0; i < m; i++ )
        {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            x[ps] = x1; y[ps] = y1; pend[pds++] = ps++;
            x[ps] = x2; y[ps] = y2; pend[pds++] = ps++;
        }
        for( int i = 0; i < c; i++ )
        {
            scanf("%d %d", &x1, &y1);
            x[i] = x1; y[i] = y1; pend[pds++] = i;
        }
        scanf("%d %d", &x1, &y1);
        x[ps] = x1; y[ps] = y1; pend[pds++] = ps; doc = ps++;
        scanf("%d %d", &x1, &y1);
        x[ps] = x1; y[ps] = y1; pend[pds++] = ps; por = ps++;

        for( int i = 0; i < ps; i++ )
            adj[i].clear();

        while( pds > 0 )
        {
            anchor = pend[0];
            int ai = 0, skipTo;
            for( int i = 1; i < pds; i++ )
                if( lexicalLess(pend[i], anchor) )
                {
                    anchor = pend[i];
                    ai = i;
                }
            swap( pend[ai], pend[pds-1] ); pds--;
            sort( pend, pend+pds, grahamLess );
            for( int p = 0; p < pds; p++ )
            {
                // Se mural
                if( c+c%2 <= pend[p] && pend[p] < doc )
                {
                    skipTo = pend[p]^1;
                    if( anchor != skipTo )
                        connect( anchor, skipTo );
                    while( grahamLess( pend[p], skipTo ) )
                    {
                        if( !properInt(anchor, pend[p], skipTo, skipTo^1) )
                            connect( anchor, pend[p] );
                        p++;
                    }
                }
                else
                    connect(anchor, pend[p]);
            }
        }

        for( int i = 0; i < c; i++ )
            for( int j = i+1; j < c; j++ )
            {
                bool free = true;
                for( int k = c+c%2; free && k < doc; k += 2 )
                    if( improperInt(i,j,k,k^1) )
                        free = false;
                if( free )
                {
                    adj[i].push_back( make_pair(j, 0LL));
                    adj[j].push_back( make_pair(i, 0LL));
                }
            }
        printf("Grafo montado.\n");
        djs(doc);
        printf("%.1f\n", sqrt(d[por]));
    }
}
