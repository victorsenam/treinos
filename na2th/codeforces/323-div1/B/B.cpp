#include <bits/stdc++.h>
#define mp make_pair
using namespace std;
typedef long long num;
const int N = 200;

num n, t, sz;
int p[N*N];
num in[N*N], tree[2*N*N], lft, ans;
num freq[301];

num query(int l, int r)
{
    num ans = 0;
    for(l+=sz, r+=sz; l<r; l>>=1, r>>=1)
    {
        if(l&1) ans = max(ans, tree[l++]);
        if(r&1) ans = max(ans, tree[--r]);
    }
    return ans;
}
void insert(int p, num x)
{
    for(tree[p+=sz] = x;p>0;p>>=1)
        tree[p>>1] = max(tree[p], tree[p^1]);
}

int main()
{
    cin >> n >> t;
    sz = n*min(n,t);

    for(int i=0;i<n;i++)
        cin >> in[i], freq[in[i]]++, p[i] = i;
    for(int i=n;i<sz;i++)
        in[i] = in[i%n], p[i] = i;
    
    sort(p, p+sz, [&](int i, int j){ return mp(in[i], i) < mp(in[j], j); });

    for(int ii=0;ii<sz;ii++)
    {
        int i = p[ii];
        insert(i, query(0, i) + num(1));
    }
    ans = query(0, sz) + max(t-n, num(0))*(*max_element(freq, freq+301));

    cout << ans << endl;
}
