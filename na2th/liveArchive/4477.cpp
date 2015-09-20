#include<bits/stdc++.h>
using namespace std;
typedef int num;
const int MS = 100003;
const int ML = 24;
char s[MS];
int p[ML][MS], sa[MS], lcp[MS], ans, n;
int fst[MS], snd[MS], id[MS];
bool lexLess(int a, int b)
{ return fst[a]==fst[b]?snd[a]<snd[b]:fst[a]<fst[b]; }
bool lexEq(int a, int b)
{ return fst[a]==fst[b]&&snd[a]==snd[b]; }
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
            fst[i] = p[k-1][i];
            snd[i] = p[k-1][min(i+(1<<(k-1)),n)];
            id[i] = i; sa[i] = i;
        }
        sort(sa,sa+n,lexLess);
        p[k][id[sa[0]]] = 0;
        for(int i=1;i<n;i++)
            p[k][id[sa[i]]] = p[k][id[sa[i-1]]] + !lexEq(sa[i],sa[i-1]);
        if(p[k][id[sa[n-1]]] == n-1 ) break;
    }
    for(int i=0;i<n;i++)
        sa[p[k][i]] = i;
    for(int i=0;i<n-1;i++)
    {
        lcp[i] = 0;
        for(int j=k;j>=0;j--)
            if( p[j][sa[i]+lcp[i]] == p[j][sa[i+1]+lcp[i]] )
            {
                lcp[i] += (1<<j);
                if(max(sa[i],sa[i+1])+lcp[i]>n) break;
            }
    }
}

int main()
{
    while( scanf(" %s", s) != EOF )
    {
        if( s[0] == '*' && !s[1] ) break;
        n = strlen(s); n++;
        build();
        ans = lcp[0];
        for(int i=1;i<n-1;i++)
            ans += max(lcp[i]-lcp[i-1], 0);
        printf("%d\n", ans);
    }
}
