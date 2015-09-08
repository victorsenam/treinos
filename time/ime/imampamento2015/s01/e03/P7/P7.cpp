#include<bits/stdc++.h>
#define MP 1005
using namespace std;
typedef int num;
typedef unsigned long long ull;

num x[MP], y[MP], n;
ull dist[MP];

inline ull dist2(int a, int b)
{ return (x[a]-x[b])*(x[a]-x[b]) + (y[a]-y[b])*(y[a]-y[b]);}

double buildTree()
{
    double ans = 0.0;
    for(int i=1; i < n; i++)
        dist[i] = ULLONG_MAX;
    dist[0] = 0;
    set< pair<ull,num> > reach; reach.insert(make_pair(0,0));
    while(!reach.empty())
    {
        int u = reach.begin()->second;
        reach.erase(reach.begin());
        ans += sqrt(dist[u]);
        dist[u] = 0;
        for(int i =0; i < n; i++)
            if( u != i && dist[i] > dist[u] + dist2(u,i) )
            {
                if( dist[i] != ULLONG_MAX )
                    reach.erase(make_pair(dist[i],i));
                dist[i] = dist[u] + dist2(u,i);
                reach.insert(make_pair(dist[i],i));
            }
    }
    return ans;
}

int main()
{
    while( scanf("%d", &n) != EOF && n )
    {
        for(int i=0; i<n;i++)
            scanf("%d %d",x+i,y+i);
        printf("%.2lf\n",buildTree());
    }
}

