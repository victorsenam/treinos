#include <bits/stdc++.h>
using namespace std;
typedef long long num;
const int T = 1e4+5;

int tree, l, r, ts;
int x[T], y[T];
int lc[T], rc[T];
int sl[T], sz[T];

int update(int t)
{
    if(t == -1) return t;
    sz[t] = 1;
    sl[t] = 0;
    if(lc[t] != -1) sl[t]  = sz[lc[t]];
    if(rc[t] != -1) sz[t] += sz[rc[t]];
    sz[t] += sl[t];
    return t;
}

void split(int t, int k)
{
    if(t == -1) return (void)(l = r = -1);
    if(k <= x[t])
         split(lc[t], k), lc[t] = r, r = t;
    else split(rc[t], k), rc[t] = l, l = t;
    update(t);
}

int merge(int tl, int tr)
{
    int ans = tl;
    if(min(tl,tr) == -1) return max(tl, tr);
    if(y[tl] > y[tr]) rc[tl] = merge(rc[tl], tr);
    else lc[ans=tr] = merge(tl, lc[tr]);
    return update(ans);
}

int find(int t, int k)
{
    if(t == -1) return 0;
    if(x[t] == k) return 1;
    if(k < x[t]) return find(lc[t], k);
    return find(rc[t], k);
}

void insert(int x)
{
    if(find(tree,x)) return;
    ::x[ts] = x;
    lc[ts] = rc[ts] = -1;
    update(ts);
    split(tree, x); 
    tree = merge(merge(l, ts++),r);
}

int query(int t, int k)
{
    if(t == -1) return 0;
    if(x[t] == k) return 1 + sl[t];
    if(k < x[t]) return query(lc[t], k);
    return sl[t] + 1 + query(rc[t], k);
}

int n, m;
int main()
{
    srand(time(NULL));
    for(int i=0;i<T;i++) y[i] = i;
    random_shuffle(y, y+T);

    tree = -1;
    scanf(" %d%d", &n, &m);
    while(m--)
    {
        char cmd;
        int in;
        scanf(" %c %d", &cmd, &in);
        int lo = 0, hi = n;
        while(lo < hi)
        {
            int mid = lo + (hi-lo)/2;
            if(mid - query(tree, mid) >= in)
                hi = mid;
            else lo = mid + 1;
        }
        in = lo;
        if(cmd == 'D') insert(in);
        else printf("%d\n", in);
    }
}
