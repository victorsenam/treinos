#include<bits/stdc++.h>
using namespace std;
typedef unsigned int num;
typedef long long ll;

const int F = 100;
const int N = 1000;
const int M = N;
num n, q, m, f, a[F], in[N][M], goal[M];
set<int> ans;

int main()
{
    freopen("filter.in", "r", stdin);
    freopen("filter.out", "w", stdout);
    scanf(" %u%u", &m, &f);
    for(int i=0;i<f;i++)
        scanf(" %u", a+i);
    scanf(" %u", &n);
    for(int j=0;j<n;j++)
        for(int i=0;i<(m+3)/4;i++)
            scanf(" %1x", &in[j][i]);

    scanf(" %u", &q);
    while(q--)
    {
        num u;
        scanf(" %u", &u);
        fill(goal, goal+m, 0);
        for(int i=0;i<f;i++)
        {
            int tgt = ll(ll(u)*ll(a[i]))%m;
            goal[tgt/4] |= (1<<(tgt%4));
        }

        for(int i=0;i<n;i++)
        {
            int ok = (ans.find(i) == ans.end());
            for(int j=0;ok && j<(m+3)/4;j++)
                ok &= !( goal[j]&(~in[i][j]) );
            if(ok)
                ans.insert(i);
        }
    }
    printf("%d", ans.size());
    for(auto it = ans.begin(); it != ans.end(); ++it)
        printf(" %d", *it);
    putchar('\n');
}
