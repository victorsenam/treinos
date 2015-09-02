#include<bits/stdc++.h>
#define MAX 500003
using namespace std;
typedef long long num;
num a[MAX], tree[MAX], n, ans, ok;

void insert(int p, num val)
{
    for(; p>0; p-=(p&-p))
        tree[p] += val;
}

num count(int p)
{
    num ans=0;
    for(;p<=n;p+=(p&-p))
        ans += tree[p];
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    for( int i=1; i<n+1;i++ )
    {
        cin >> a[i];
        a[i] += a[i-1];
    }
    if( a[n]%3 != 0 )
    {
        cout << 0 << endl;
        return 0;
    }
    if( a[n] == 0 )
    {
        for(int i=1;i<n;i++)
            if(a[i] == 0)
                ans++;
        cout << ans*(ans-1)/2 << endl;
        return 0;
    }

    for( int i=1;i<n;i++)
        if( a[i] == 2*(a[n]/3) )
            insert(i-1, 1);

    for( int i=1;i<n;i++)
        if( a[i] == a[n]/3 )
            ans += count(i);

    cout << ans << endl;
}
