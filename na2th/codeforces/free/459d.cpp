#include<bits/stdc++.h>
#define mp make_pair
#define pb push_back
using namespace std;
typedef long long num;
const int N = 1e6;

int n;
num tree[2*N];

num query(int l, int r)
{
    num ans = 0;
    for(l+=n, r+=n;l<r;l>>=1,r>>=1)
    {
        if(l&1) ans += tree[l++];
        if(r&1) ans += tree[--r];
    }
    return ans;
}
void insert(int p, num x)
{
    for(tree[p+=n]=x;p>0;p>>=1)
        tree[p>>1] = tree[p] + tree[p^1];
}

num in[N], ans;
num seen[N], freq[N];
num sf[N], pf[N];
int ss;
vector<pair<num, int> > q;

int main()
{
    scanf(" %d", &n);
    for(int i=0;i<n;i++)
        scanf(" %I64d", in+i), seen[ss++] = in[i];
    sort(seen, seen+ss);
    ss = unique(seen, seen+ss) - seen;
    for(int i=0;i<n;i++)
        pf[i] = ++freq[lower_bound(seen, seen+ss, in[i]) - seen];
    fill(freq, freq+ss, 0);
    for(int i=n-1;i>=0;--i)
        sf[i] = ++freq[lower_bound(seen, seen+ss, in[i]) - seen];
    for(int i=0;i<n;i++)
        q.pb(mp(pf[i], i<<1)), q.pb(mp(sf[i], i<<1|1));
    sort(q.begin(), q.end());
    for(int i=0;i<q.size();i++)
    {
        int k = q[i].second>>1;
        if(q[i].second&1) insert(k, 1);
        else ans += query(k+1, n);
    }
    printf("%I64d\n", ans);
}
