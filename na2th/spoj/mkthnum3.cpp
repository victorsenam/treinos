#include <bits/stdc++.h>
#define mp make_pair
using namespace std;
typedef long long num;
const int N = 1e5;
const int T = 2*17*N;

int n, m;
int in[N], tree[N+1], p[N], q[N];
int sum[T], lc[T], rc[T], base, ts;

int build(int t, int l, int r)
{
    if(l+1 == r) return sum[t] = 0, t;
    int mid = (l+r)>>1;
    lc[t] = build(ts++, l, mid);
    rc[t] = build(ts++, mid, r);
    sum[t] = sum[lc[t]] + sum[rc[t]];
    return t;
}

int update(int t, int l, int r, int p)
{
    int n = ts++;
    lc[n] = lc[t], rc[n] = rc[t], sum[n] = sum[t];
    if(l+1 == r) return sum[n] += 1, n;
    int mid = (l+r)>>1;
    if(p < mid) lc[n] = update(lc[n], l, mid, p);
    else        rc[n] = update(rc[n], mid, r, p);
    sum[n] = sum[lc[n]] + sum[rc[n]];
    return n;
}

int get(int tr, int tq, int l, int r, int k)
{
    if(l+1 == r) return l;
    int mid = (l+r)>>1, lft = sum[lc[tq]]-sum[lc[tr]];
    if(lft < k)
         return get(rc[tr], rc[tq], mid, r, k-lft);
    else return get(lc[tr], lc[tq], l, mid, k);
}

int inLess(int i, int j)
{ return in[i] < in[j]; }
int main()
{
    scanf(" %d%d", &n, &m);
    for(int i=0;i<n;i++)
        scanf(" %d", in+i), p[i] = i;
    sort(p, p+n, inLess);
    for(int i=0;i<n;i++) q[p[i]] = i;
    tree[0] = build(ts++, 0, n);
    for(int i=0;i<n;i++) tree[i+1] = update(tree[i], 0, n, q[i]);
    while(m--)
    {
        int i, j, k;
        scanf(" %d%d%d", &i, &j, &k);
        printf("%d\n", in[p[get(tree[--i], tree[j], 0, n, k)]]);
    }
}
