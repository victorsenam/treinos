#include <bits/stdc++.h>
using namespace std;
typedef int num;
typedef int node;
typedef double cood;
typedef complex<cood> point;
const int N = 1e3+2;
const cood eps = 1e-9;
int w, n, l, r, id[N], seen[N], turn;
cood ix, iy, x[N], y[N];
inline cood dist(int i, int j)
{ return sqrt( (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]) ); }

node find(node u)
{ 
    if(seen[u] != turn)
        id[u] = -1, seen[u] = turn;
    return id[u] < 0 ? u : (id[u]=find(id[u])); 
}
int merge(node u, node v)
{
    if( (u=find(u)) == (v=find(v)) ) return 0;
    if(id[u] < id[v]) swap(u,v);
    id[v] += id[u]; id[u] = v; return 1;
}

int guess(cood g)
{
    turn++;
    for(int i=0;i<n;i++)
    {
        if(x[i] < g + eps)
            merge(l,i);
        if(w-x[i] < g + eps)
            merge(i,r);
    }
    for(node u=0;u<n;u++)
        for(node v=u+1;v<n;v++)
            if( dist(u,v) < g + eps)
                merge(u,v);
    if(find(l) == find(r))
    {
        ix = x[0], iy = y[0];
        return 1;
    }
    for(node u=0;u<n;u++)
        for(node v=u+1;v<n;v++)
            if( (find(u) == find(l) && find(v) == find(r)) ||
                (find(v) == find(l) && find(u) == find(r)) )
            {
                if(.5*dist(u,v) < g + eps)
                {
                    ix = .5*(x[u]+x[v]), iy = .5*(y[u]+y[v]);
                    return 1;
                }
            }
    for(node u=0;u<n;u++)
        if(find(u) == find(r) && .5*x[u] < g + eps)
        {
            ix = .5*x[u], iy = y[u];
            return 1;
        }
    for(node v=0;v<n;v++)
        if(find(v) == find(l) && .5*(w-x[v]) < g + eps)
        {
            ix = .5*(x[v]+w), iy = y[v];
            return 1;
        }

    return 0;
}

int main()
{
    freopen("froggy.in", "r", stdin);
    freopen("froggy.out", "w", stdout);
    scanf(" %d%d", &w, &n);
    l = n; r = n+1;
    for(int i=0;i<n;i++)
        scanf(" %lf%lf", x+i, y+i);
    cood lo = 0, hi = .5*w;
    while( hi-lo > .01 )
    {
        cood mid = (hi+lo)/2.;
        if( guess(mid) )
            hi = mid;
        else lo = mid;
    }
    guess(lo);
    printf("%.5lf %.5lf\n", ix, iy);
}
