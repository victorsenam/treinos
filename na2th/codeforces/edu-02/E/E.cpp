#include <bits/stdc++.h>
#define mp make_pair
using namespace std;
typedef long long num;
typedef int node;
typedef int edge;

const int N = 1.1e5;
int n, c[N];
int hd[N], nx[2*N], to[2*N], es;
int id[N], lbl[N];
node curr;
int bf[N];
num ans[N], acc[N];
map<int,int> freq[N];
map<int,num> sol[N];

int find(node u)
{ return id[u] < 0 ? u : find(id[u]); }
void merge_solutions(node u, node v)
{
    for(auto it=freq[v].begin();it!=freq[v].end(); ++it)
    {
        freq[u][it->first] += it->second;
        sol[u][freq[u][it->first]] += num(it->first);
    }
}
int merge(node u, node v)
{
    if( id[u=find(u)] < id[v=find(v)] ) swap(u,v);
    merge_solutions(v,u);
    id[v] += id[u];
    id[u] = v;
    return 1;
}

void dfs(node u)
{
    lbl[u] = 1;
    acc[u] = ans[u] = num(c[u]);
    bf[u] = 1;
    freq[u][c[u]] = 1;
    sol[u].insert(mp(1,c[u]));
    for(edge e=hd[u];e!=-1;e=nx[e])
        if(!lbl[to[e]])
        {
            dfs(to[e]);
            merge(curr=u, to[e]);
        }
    ans[u] = sol[find(u)].rbegin()->second;
}

int main()
{
    scanf(" %d", &n);
    assert(2*(n-1) < 2*N);
    memset(hd, -1, sizeof hd);
    memset(id, -1, sizeof id);
    for(int i=0;i<n;i++)
        scanf(" %d", c+i);
    for(int i=0;i<n-1;i++)
    {
        node u, v;
        scanf(" %d%d", &u, &v); u--; v--;
        to[es] = v; nx[es] = hd[u]; hd[u] = es++;
        to[es] = u; nx[es] = hd[v]; hd[v] = es++;
    }
    dfs(0);
    for(node u=0;u<n;u++)
        cout << ans[u] << ' ';
    putchar('\n');
}
