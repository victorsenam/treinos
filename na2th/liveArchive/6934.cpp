#include <bits/stdc++.h>
using namespace std;
typedef long long num;
typedef int node;
typedef int edge;
int n, t;
vector<int> sol;
bool adj[10][10];

void gen(int u, int curr)
{
    if(curr > 300) return;
    sol.push_back(curr);
    for(node v=0;v<10;v++)
        if(adj[u][v])
            gen(v, 10*curr + v);
}

int main()
{
    adj[0][0] = 1;
    for(int i=1;i<10;i++)
        adj[i][0] = (i-1)%3 <= 1;
    for(int i=1;i<10;i++)
        for(int j=1;j<10;j++)
            adj[i][j] = (i-1)/3 <= (j-1)/3 && (i-1)%3 <= (j-1)%3;

    for(int i=1;i<10;i++)
        gen(i, i);
    sort(sol.begin(), sol.end());
    scanf(" %d", &t);
    while(t--)
    {
        scanf(" %d", &n);
        int p = lower_bound(sol.begin(), sol.end(), n) - sol.begin(),
            ans = p;
        if(p > 0 && abs(sol[p-1]-n) < abs(sol[ans]-n))
            ans = p-1;
        if(p+1 < sol.size() && abs(sol[p+1]+n) < abs(sol[ans]-n))
            ans = p+1;
        printf("%d\n", sol[ans]);
    }
}
