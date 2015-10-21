#include<bits/stdc++.h>
using namespace std;
typedef int num;
const int MS = 250007;
const int ML = 20;
char s[MS];
int n;
int p[ML][MS],
    fst[MS], snd[MS], id[MS],
    lcp[MS], sa[MS];
int q[MS], qf, qb;
int m[MS], mf, mb;
double ans;

bool lexLess(int i, int j)
{ return fst[i] == fst[j] ? snd[i] < snd[j] : fst[i] < fst[j]; }
bool lexEq(int i, int j)
{ return fst[i] == fst[j] && snd[i] == snd[j]; }

void build()
{
    n = strlen(s);
    int k;
    for(int i=0;i<n;i++)
        p[0][i] = s[i] - 'a';
    for(k = 1;k<20;k++)
    {
        for(int i=0;i<n;i++)
        {
            fst[i] = p[k-1][i];
            snd[i] = i + (1<<(k-1)) < n ? p[k-1][i+(1<<(k-1))] : -1;
            id[i] = sa[i] = i;
        }
        sort(sa, sa+n, lexLess);
        p[k][id[sa[0]]] = 0;
        for(int i=1;i<n;i++)
            p[k][id[sa[i]]] = p[k][id[sa[i-1]]] + !lexEq(sa[i],sa[i-1]);
        if( p[k][id[sa[n-1]]] == n-1 ) break;
    }
    for(int i=0;i<n;i++)
        sa[p[k][i]] = i;
    for(int i=0;i<n-1;i++)
    {
        lcp[i] = 0;
        for(int j=k-1;j>=0;j--)
            if( p[j][sa[i] + lcp[i]] == p[j][sa[i+1] + lcp[i]] )
            {
                lcp[i] += (1<<j);
                if( max(sa[i],sa[i+1]) + lcp[i] > n ) break;
            }


    }
}

void insert(int x)
{
    while( mf < mb && m[mb-1] > x )
        mb--;
    m[mb++] = q[qb++] = x;
}

void remove()
{
    mf += (q[qf] == m[mf]);
    qf++;
}

int main()
{
    ans = 0.0;
    scanf("%d %s", &n, s);
    for(int i=0;i<n;i++)
        s[n+i] = s[i];
    s[2*n] = CHAR_MAX;
    s[2*n+1] = 0;
    build();
    for(int i=0;i<n;i++)
        printf("[%d]%s\n", n-sa[i], s+sa[i]);
}
