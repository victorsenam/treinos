#include<bits/stdc++.h>
using namespace std;
typedef long long num;
const num MOD = 1e9 + 7;
const int MN = 100001;
num seven[MN], dosSeven[MN], n;

inline num mod(num x)
{ return (x%MOD + MOD)%MOD; }

int main()
{
    seven[0] = dosSeven[0] = 1ll;
    for(int i=1;i<MN;i++)
        seven[i] = mod(7ll*seven[i-1]), dosSeven[i] = mod(27ll*dosSeven[i-1]);

    cin >> n;
    num ans = 0ll;
    for(int i=0;i<n;i++)
        ans = mod(ans + mod(mod(20ll*seven[i])*dosSeven[n-i-1]));
    cout << ans << endl;
}
