#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define all(a) a.begin(), a.end()
using namespace std;
typedef long long num; 
const int N = 1e5;
const int T = 20*N;

int n, m, ps;
int in[N], p[N];

int tree[N+1], lc[T], rc[T], sum[T], ts, t_ans;

int build(int t, int l, int r)
{
    if(l+1 == r) return sum[t] = 0, t;
    int mid = (l+r)>>1;
    lc[t] = build(ts++, l, mid);
    rc[t] = build(ts++, mid, r);
    sum[t] = sum[lc[t]] + sum[rc[t]];
    return t;
}

int update(int t, int l, int r, int p, num x)
{
    int n = ts++;
    lc[n] = lc[t], rc[n] = rc[t];
    if(l+1 == r) return sum[n] = x, n;
    int mid = (l+r)>>1;
    if(p < mid) lc[n] = update(lc[n], l, mid, p, x);
    else        rc[n] = update(rc[n], mid, r, p, x);
    sum[n] = sum[lc[n]] + sum[rc[n]];
    return n;
}

void get(int t, int l, int r, int ql, int qr)
{
    if(ql >= r || qr <= l) return;
    if(ql <= l && r <= qr) return (void)(t_ans += sum[t]);
    int mid = (l+r)>>1;
    get(lc[t], l, mid, ql, qr);
    get(rc[t], mid, r, ql, qr);
}

int main()
{
    scanf(" %d%d", &n, &m);
    for(int i=0;i<n;i++)
        scanf(" %d", in+i), p[i] = i;
    sort(p, p+n, [](int i, int j){ return mp(in[i],i) < mp(in[j],j); });
    ts = 0;
    tree[0] = build(ts++, 0, n);
    for(int i=0;i<n;i++)
        tree[i+1] = update(tree[i], 0, n, p[i], 1);
    while(m--)
    {
        int l, r, k;
        scanf(" %d%d%d", &l, &r, &k); --l;
        int lo = 0, hi = n;
        while(lo < hi)
        {
            int mid = lo + (1+hi-lo)/2;
            t_ans = 0;
            get(tree[mid], 0, n, l, r);
            if(t_ans < k) lo = mid;
            else          hi = mid-1;
        }
        printf("%d\n", in[p[lo]]);
    }
}
