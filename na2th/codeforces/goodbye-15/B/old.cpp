#include <bits/stdc++.h>
using namespace std;
typedef long long num;
num a, b;
num st, nd, guess;
num ans;

int main()
{
    cin >> a >> b;
    for(st = 1ll; st-1< a ;st<<=1);
    for(nd = 1ll; nd-1<=b; nd<<=1); nd >>= 1;
    for(int i=0;(1ll<<i)<st;i++)
    {
        guess = st - 1ll - (1ll<<i);
        ans += (a <= guess && guess <= b);
    }
    st <<= 1;
    while(st <= nd)
    {
        ans += 62 - __builtin_clzll(st);
        st <<= 1;
    }
    cout << ans << endl;
}
