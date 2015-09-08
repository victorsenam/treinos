#include <bits/stdc++.h>

using namespace std;

#define MAX_N 110

int n, r;
int adj[MAX_N][MAX_N];
int ctr[MAX_N];
double memo[11000][110];

double pd (int amount, int npath)
{
    double &m = memo[amount][npath];
    if (m >= 0) return m;
    if (npath == 1)
    {
        if (amount >= r)
            m = 1.0;
        else m = (1.0*amount)/(1.0*r);
        return m;
    }
    m = 0;
    bool found = false;
    for (int i = 1; i <= r && i <= amount; i++)
    {
        found = true;
        m += pd(amount-i, npath-1);
    }
    if (!found) m = 0;
    else m /= (1.0*r);
    return m;
}

int main()
{
    int t;
    scanf("%d", &t);
    for (int cas = 0; cas < t; cas++)
    {
        scanf("%d %d", &n, &r);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                char c;
                scanf(" %c", &c);
                adj[i][j] = c == 'Y' ? 1 : 0;
            }
        }
        int cpl;
        scanf("%d", &cpl);
        printf("Case %d\n", cas+1);
        for (int i = 0; i < cpl; i++)
        {
            int a, b, m;
            scanf("%d %d %d", &a, &b, &m);
            a--; b--;
            queue <int> q;
            q.push(a);
            for (int j = 0; j < n; j++)
                ctr[j] = -1;
            ctr[a] = 0;
            while (!q.empty())
            {
                int d = q.front();
                //printf("d:%d %d\n", d, ctr[d]);
                q.pop();
                if (d == b) break;
                for (int j = 0; j < n; j++)
                {
                    if (adj[d][j] && ctr[j] < 0)
                    {
                        q.push(j);
                        ctr[j] = ctr[d] + 1;
                    }
                }
            }
            for (int i = 0; i <= m; i++)
                for (int j = 0; j <= ctr[b]; j++)
                    memo[i][j] = -1;
            printf("%lf\n", pd(m, ctr[b]));
        }
        if (cas < t-1)
            printf("\n");
    }
}
