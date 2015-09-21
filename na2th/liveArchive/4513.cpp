#include<bits/stdc++.h>
using namespace std;
typedef int num;
const int MS = 40007;
const int ML = 20;
char s[MS];
int n, m, ans, pos;
int sa[MS], p[ML][MS], lcp[MS][ML], sam[MS][ML];
int lo[MS], hi[MS], id[MS];
bool lexLess(int a, int b)
{ return lo[a]==lo[b]?hi[a]<hi[b]:lo[a]<lo[b]; }
bool lexEq(int a,int b)
{ return lo[a]==lo[b]&&hi[a]==hi[b]; }

void build()
{
    int k;
    for(int i=0;i<ML;i++)
        p[i][n] = -1;
    for(int i=0;i<n;i++)
        p[0][i] = s[i];
    for(k=1;k<ML;k++)
    {
        for(int i=0;i<n;i++)
        {
            lo[i] = p[k-1][i];
            hi[i] = p[k-1][min(i+(1<<(k-1)),n)];
            id[i] = i; sa[i] = i;
        }
        sort(sa, sa+n, lexLess);
        p[k][id[sa[0]]] = 0;
        for(int i=1;i<n;i++)
            p[k][id[sa[i]]] = p[k][id[sa[i-1]]] + !lexEq(sa[i],sa[i-1]);
        if(p[k][id[sa[n-1]]] == n-1 ) break;
    }
    for(int i=0;i<n;i++)
        sa[p[k][i]] = sam[p[k][i]][0] = i;
    for(int i=0;i<n-1;i++)
    {
        lcp[i][0] = 0;
        for(int j=k;j>=0;j--)
            if( p[j][sa[i]+lcp[i][0]] == p[j][sa[i+1]+lcp[i][0]] )
            {
                lcp[i][0] += (1<<j);
                if( max(sa[i],sa[i+1])+lcp[i][0] >= n ) break;
            }
    }
    for(int j=1;j<ML;j++)
        for(int i=0;i<n;i++)
            if( i+(1<<(j-1)) < n )
                sam[i][j] = max(sam[i][j-1],sam[i-(1<<(j-1))][j-1]);
            else
                sam[i][j] = INT_MIN;

    for(int j=1;j<ML;j++)
        for(int i=0;i<n-1;i++)
            if( i + (1<<(j-1)) < n-1 )
                lcp[i][j] = min(lcp[i][j-1],lcp[i+(1<<(j-1))][j-1]);
            else
                lcp[i][j] = INT_MAX;
}

int main()
{
    while( scanf("%d", &m) != EOF && m )
    {
        scanf("%s", s);
        n = strlen(s);
        build();
        int k = 31 - __builtin_clz(m);
        ans = -1;
        for(int i=0;i+m<n;i++)
            if( min(lcp[i][k],lcp[i+m-(1<<k)][k]) >= ans )
            {
                ans = min(lcp[i][k],lcp[i+m-(1<<k)][k]);
                pos = max(sam[i+1][k],sam[i+1+m-(1<<k)][k]);
            }
        if(ans > 0)
            printf("%d %d\n", ans+1, pos-1);
        else
            printf("none\n");
    }
}
