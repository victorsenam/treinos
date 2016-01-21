#include<bits/stdc++.h>
using namespace std;
typedef int num;
const int MS = 5e5+2;
const int ML = 30;
char s[MS];
int n;
int rnk[MS],
    fst[MS], snd[MS],
    lcp[MS], sa[MS];

void cnt_sort(int * v, int u)
{
    int * f = lcp, *aux = rnk;
    for(int i=0;i<u;i++) f[i] = 0;
    for(int i=0;i<n;i++) f[v[i]+1]++;
    for(int i=1;i<u;i++) f[i] += f[i-1];
    for(int i=0;i<n;i++) aux[f[v[sa[i]]]++] = sa[i];
    for(int i=0;i<n;i++) sa[i] = aux[i];
}

bool lexLess(int i, int j)
{ return fst[i] == fst[j] ? snd[i] < snd[j] : fst[i] < fst[j]; }
void build_sa()
{
    n = strlen(s);
    int k, u = 0;
    for(int i=0;i<n;i++) u = max(u, rnk[i] = s[i]);
    for(k=1;k<ML;k++)
    {
        rnk[n] = 0;
        for(int i=0;i<n;i++)
        {
            fst[i] = rnk[sa[i] = i];
            snd[i] = rnk[min(i+(1<<(k-1)), n)];
        }
        cnt_sort(snd, ++u);
        cnt_sort(fst,   u);
        rnk[sa[0]] = 1;
        for(int i=1;i<n;i++)
            rnk[sa[i]] = rnk[sa[i-1]] + (fst[sa[i-1]] != fst[sa[i]] || snd[sa[i-1]] != snd[sa[i]]);
        if((u = rnk[sa[n-1]]) == n) break;
    }
    for(int i=0;i<n;i++) sa[--rnk[i]] = i;
    int h = 0;
    for(int i=0;i<n;i++)
        if(rnk[i] == n-1) h = 0;
        else
        {
            int j = sa[rnk[i]+1];
            while(i+h < n && j+h < n && s[i+h] == s[j+h]) h++;
            lcp[rnk[i]]=h;
            h -= (!!h);
        }
}

int *q, qf, qb;
int *m, mf, mb;
int ss;
double ans;
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
    for(int i=0;i<n;i++) s[n+i] = s[i];
    s[2*n]   = CHAR_MAX;
    s[2*n+1] = 0;
    build_sa();
    q = fst;
    m = snd;
    int pos = 0;
    while( n-1-sa[pos] <= n/2 ) pos++;
    insert(lcp[pos++]);
    while( pos < n-1 )
    {
        if( n-1-sa[pos] > n/2 )
        {
            ans += min(m[mf],n/2);
            ss++;
            qf = qb;
            mf = mb;
        }
        insert(lcp[pos++]);
    }
    ans /= ss;
    printf("%.3lf\n", ans);
}
