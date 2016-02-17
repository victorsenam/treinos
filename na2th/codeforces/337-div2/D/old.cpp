#include <bits/stdc++.h>
#define mp make_pair
using namespace std;
typedef long long num;
typedef int node;
typedef int edge;

const int N = 1e5+3;
set<pair<num, pair<num,num> > > h, v;
set<pair<num, num> > r;
num ix0, iy0, ix1, iy1, seen[4*N], ans;
int n, ss;

num tree[4*N];

void change(int p, int v)
{
    for(tree[p+=ss]=v;p>1;p>>=1)
        tree[p>>1] = tree[p] + tree[p^1];
}

num get(int l, int r)
{
    num ans = 0;
    for(l+=ss,r+=ss;l<r;l>>=1,r>>=1)
    {
        if(l&1) ans += tree[l++];
        if(r&1) ans += tree[--r];
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++)
    {
        cin >> ix0 >> iy0 >> ix1 >> iy1;
        seen[ss++] = ix0;
        seen[ss++] = iy0;
        seen[ss++] = ix1;
        seen[ss++] = iy1;
        if(ix1<ix0) swap(ix0, ix1);
        if(iy1<iy0) swap(iy0, iy1);
        if(ix0 == ix1)
            v.insert(mp(ix0, mp(iy0,iy1)));
        else
            h.insert(mp(iy0, mp(ix0,ix1)));
    }
    sort(seen, seen+ss);
    ss = unique(seen, seen+ss) - seen;
    for(auto it=h.begin();it!=h.end();)
    {
        num curr  = it->first,
            start = it->second.first,
            reach = it->second.second;
        while(it!=h.end() && it->first == curr && it->second.first <= reach)
        {
            reach = max(it->second.second, reach);
            ++it;
        }
        ans += (reach - start + num(1));
    }
    for(auto it=h.begin();it!=h.end();++it)
    {
        r.insert(mp(it->second.first, it->first));
        r.insert(mp(it->second.second, it->first));
    }
    for(auto it=v.begin();it!=v.end();)
    {
        num curr  = it->first,
            start = it->second.first,
            reach = it->second.second;
        while(!r.empty() && r.begin()->first <= curr)
        {
            int x = lower_bound(seen, seen+ss, r.begin()->second) - seen;
            change(x, tree[x+ss]^1);
            r.erase(r.begin());
        }
        while(it != v.end() && it->first == curr && it->second.first <= reach)
        {
            reach = max(it->second.second, reach);
            ++it;
        }
        int lo = lower_bound(seen, seen+ss, start) - seen,
            hi = lower_bound(seen, seen+ss, reach) - seen;
        ans += (reach - start + 1) - get(lo, hi+1);
    }
    cout << ans << endl;
}
