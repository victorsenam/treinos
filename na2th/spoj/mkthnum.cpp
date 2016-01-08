#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define all(a) a.begin(), a.end()
using namespace std;
typedef long long num; 
const int N = 1e5;

int n, ss;
int ans;
int in[N], seen[N];
int m;
vector<int> tree[2*N];

void query(int l, int r, int k)
{
    if(l >= r) return;
    if(l&1)
    {
        ans += lower_bound(all(tree[l]), k) - tree[l].begin();
        l++;
    }
    if(r&1)
    {
        --r;
        ans += lower_bound(all(tree[r]), k) - tree[r].begin();
    }
    query(l>>1, r>>1, k);
}

int main()
{
    scanf(" %d%d", &n, &m);
    for(int i=0;i<n;i++)
    {
        scanf(" %d", in+i);
        seen[ss++] = in[i];
    }
    sort(seen, seen+ss);
    ss = unique(seen, seen+ss) - seen;
    for(int i=0;i<n;i++)
        tree[i+n].pb(in[i]);
    for(int i=n-1;i>0;--i)
        merge(all(tree[i<<1]), all(tree[i<<1|1]), back_inserter(tree[i]));
    while(m--)
    {
        int i, j, k;
        scanf(" %d%d%d", &i, &j, &k); --i;
        int lo = 0, hi = ss-1;
        while(lo < hi)
        {
            int mid = lo + (1+hi-lo)/2;
            ans = 0; query(i+n, j+n, seen[mid]);
            if(ans < k) lo = mid;
            else hi = mid-1; 
        }
        printf("%d\n", seen[lo]);
    }
}
