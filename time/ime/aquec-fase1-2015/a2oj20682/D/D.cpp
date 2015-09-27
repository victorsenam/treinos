#include<bits/stdc++.h>
using namespace std;
typedef long long num;
typedef int node;
typedef int edge;
typedef double cood;
typedef complex<cood> point;
const int MN = 1003;
const int ME = 2*MN*MN;
const cood eps = 1e-9;

int seen[MN], ans[MN][2], head[MN];
point p[MN];
num r[MN];
int to[ME], next[ME], es;
int n;

num gcd(num a, num b)
{ return (b==0) ? a : gcd(b, a%b); }

void dfs(node u, num m, num d, num ri)
{
    seen[u] = 1;
    ans[u][0] = -m*ri;
    ans[u][1] = d*r[u];
    num aux = gcd(abs(ans[u][0]), abs(ans[u][1]));
    ans[u][0] /= aux; ans[u][1] /= aux;
    for(edge e=head[u];e>=0;e=next[e])
        if(!seen[to[e]])
            dfs(to[e], ans[u][0], ans[u][1], r[u]);
}

int main()
{
    int tc; scanf("%d", &tc);
    while(tc--)
    {
        memset(head ,-1, sizeof head); es = 0;
        scanf("%d", &n);
        for(int i=0;i<n;i++)
        {
            cood nx,ny;
            num nr;
            scanf("%lf %lf %lld", &nx, &ny, &nr);
            p[i] = point (nx, ny);
            r[i] = nr;
        }
        for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            if( abs(p[i]-p[j]) < r[i] + r[j] + eps )
            {
                to[es] = j; next[es] = head[i]; head[i] = es++;
                to[es] = i; next[es] = head[j]; head[j] = es++;
            }
        memset(seen, 0, sizeof seen);
        dfs(0, -1, 1, r[0]);
        for(int i=0; i<n; i++)
            if(seen[i])
            {
                if(abs(ans[i][1]) == 1)
                    printf("%d ", abs(ans[i][0]) );
                else
                    printf("%d/%d ", abs(ans[i][0]), abs(ans[i][1]));
                if(ans[i][0] > 0ll)
                    printf("clockwise\n");
                else
                    printf("counterclockwise\n");
            }
            else
                printf("not moving\n");
    }
}
