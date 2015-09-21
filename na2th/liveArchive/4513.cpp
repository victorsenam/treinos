#include<bits/stdc++.h>
using namespace std;
typedef int num;
const int MS = 40007;
const int ML = 20;
char s[MS];
int sa[MS], lcp[MS], n, m, ans, aux, pos;
int lo[MS], hi[MS], id[MS], p[ML][MS];
bool lexLess(int i,int j)
{ return lo[i]==lo[j]?hi[i]<hi[j]:lo[i]<lo[j]; }
bool lexEq(int i, int j)
{ return lo[i]==lo[j]&&hi[i]==hi[j]; }

void buildSA()
{
    int k;
    for(int i=0;i<ML;i++)
        p[i][n] = -1;
    for(int i=0;i<MS;i++)
        p[0][i] = s[i];
    for(k=1;k<ML;k++)
    {
        for(int i=0;i<n;i++)
        {
            lo[i] = p[k-1][i];
            hi[i] = p[k-1][min(n,i+(1<<(k-1)))];
            id[i] = i; sa[i] = i;
        }
        sort(sa, sa+n, lexLess);
        p[k][id[sa[0]]] = 0;
        for(int i=1;i<n;i++)
            p[k][id[sa[i]]] = p[k][id[sa[i-1]]] + !lexEq(sa[i],sa[i-1]);
        if( p[k][id[sa[n-1]]] == n-1 ) break;
    }
    for(int i=0;i<n;i++)
        sa[p[k][i]] = i;
    lcp[n-1] = 0;
    for(int i=0;i<n-1;i++)
    {
        lcp[i] = 0;
        for(int j=k;j>=0;j--)
            if( p[j][ sa[i]+lcp[i] ] == p[j][ sa[i+1]+lcp[i] ] )
            {
                lcp[i] += (1<<j);
                if( max(sa[i],sa[i+1])+lcp[i] > n ) break;
            }
    }
 }

int lt[2*MS], st[2*MS];
void buildT()
{
    for(int i=0;i<n;i++)
    {
        st[n+i] = sa[i];
        lt[n+i] = lcp[i];
    }
    for(int i=n-1;i>0;i--)
    {
        st[i] = max(st[i<<1],st[i<<1|1]);
        lt[i] = min(lt[i<<1],lt[i<<1|1]);
    }
}

int lcpQuery(int l, int r)
{
    int ans = n;
    for(l+=n,r+=n;l<r;l>>=1,r>>=1)
    {
        if(l&1) ans = min(ans,lt[l++]);
        if(r&1) ans = min(ans,lt[--r]);
    }
    return ans;
}

int saQuery(int l, int r)
{
    int ans = 0;
    for(l+=n,r+=n;l<r;l>>=1,r>>=1)
    {
        if(l&1) ans = max(ans, st[l++]);
        if(r&1) ans = max(ans, st[--r]);
    }
    return ans;
}

int main()
{
    while( scanf("%d", &m) && m )
    {
        scanf("%s", s);
        n = strlen(s);
        buildSA();
        buildT();
        ans = 0;
        pos = 0;
        for(int i=0;i+m-1<n+1;i++)
        {
            if( (aux=lcpQuery(i,i+m-1)) >= ans )
            {
                if( aux > ans )
                    pos = saQuery(i,i+m);
                else
                    pos = max(pos, saQuery(i,i+m));
                ans = max(ans, aux);
            }
        }
        if( ans != 0 && ans < n)
            printf("%d %d\n", ans, pos);
        else if( ans != 0 )
            printf("%d %d\n", ans, 0);
        else
            printf("none\n");
    }
}
