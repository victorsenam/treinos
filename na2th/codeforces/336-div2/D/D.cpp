#include<bits/stdc++.h>
using namespace std;
typedef long long num;
typedef int node;
typedef int edge;

const int N = 500;
int n, cs, c[N], aux[N], as, found;
int pal[N][N];
int bst[N], reach[N], ans;

bool isPal(int i, int j)
{
    if(pal[i][j] != -1)
        return pal[i][j];
    if(i>=j) pal[i][j] = 1;
    else pal[i][j] = (c[i] == c[j] && isPal(i+1, j-1));
    return pal[i][j];
}

int main()
{
    scanf("%d", &n);
    for(int i=0;i<n;i++) scanf(" %d", c+i);
    ans = 0;
    while(n>0)
    {
        memset(pal, -1, sizeof pal);
        found = 0;
        for(int i=0;i<n;i++)
        {
            bst[i] = i;
            for(int j=i;j<n;j++)
                if( isPal(i,j) )
                {
                    found++;
                    bst[i] = max(bst[i], j);
                }
            reach[i] = bst[i] - i;
        }
        if(found == n)
        {
            ans += n;
            break;
        }
        else
        {
            int flag = 0;
            as = 0;
            int goal = *max_element(reach, reach+n);
            for(int i=0;i<n;i++)
            {
                if(!flag && reach[i] == goal)
                {
                    i = bst[i];
                    flag = 1;
                }
                else aux[as++] = c[i];
            }
            n = as;
            for(int i=0;i<n;i++)
                c[i] = aux[i];
            ans++;
        }
    }
    printf("%d\n", ans);
}
