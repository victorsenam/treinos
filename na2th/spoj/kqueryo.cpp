#include <bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long num;
const int N = 3e4;
int n, q;
vector<int> tree[2*N];
int in, last_ans;

template<typename T> T& getnum(T& t)
{
    char c; T s=1;
    while(isspace(c=getchar()));
    if(feof(stdin)) exit(0);
    if(c=='-') s=-1,c=getchar();
    t = c-'0';
    while(isdigit(c=getchar())) t = (t<<3)+(t<<1)+c-'0';
    return t*=s;
}
template<typename T,typename... Ts> void getnum(T& t, Ts&... ts)
{ getnum(t); getnum(ts...); }

bool inRange(int l, int i, int h)
{ return l <= i && i <= h; }
int query(int l, int r, int k)
{
    int ans = 0;
    if(l >= r) return ans;
    if(l&1)
    {
        ans += tree[l].end() - upper_bound(tree[l].begin(), tree[l].end(), k);
        l++;
    }
    if(r&1)
    {
        --r;
        ans += tree[r].end() - upper_bound(tree[r].begin(), tree[r].end(), k);
    }
    return ans + query(l>>1, r>>1, k);
}

int main()
{
    getnum(n);
    for(int i=0;i<n;i++)
    {
        getnum(in);
        tree[i+n].pb(in);
    }
    for(int i=n-1;i>0;--i)
    {
        for(int x : tree[i<<1]) tree[i].pb(x);
        for(int x : tree[i<<1|1]) tree[i].pb(x);
        sort(tree[i].begin(), tree[i].end());
    }
    getnum(q);
    while(q--)
    {
        int a, b, c;
        getnum(a,b,c);
        a ^= last_ans;
        b ^= last_ans;
        c ^= last_ans;
        a = max(a,1);
        b = min(b,n);
        if(a <= b)
             last_ans = query(--a+n, b+n, c);
        else last_ans = 0;
        printf("%d\n", last_ans);
    }
}
