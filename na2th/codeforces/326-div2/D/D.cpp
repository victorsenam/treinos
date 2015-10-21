#include<bits/stdc++.h>
using namespace std;
typedef long long num;
typedef int node;
typedef int edge;
const num MOD = 1000000007;
const int MN = 2000001;
num n, l, k, ps;
int x;
num pos[MN], aux[MN], in[MN], ans;

map<int, int> freq;
map<int, int>::iterator it;

inline num mod(num x)
{ return (x%MOD + MOD)%MOD; }

int main()
{
    cin >> n >> l >> k;
    for(int i=0;i<n;i++)
    {
        cin >> in[i];
        if( freq.find(in[i]) == freq.end() )
            freq[in[i]] = 1;
        else
            freq[in[i]] = freq[in[i]]+1;
    }

    x = min(l/n + !!(l%n), k);
    for(it = freq.begin(); it!=freq.end(); ++it)
        pos[ps++] = it->second;

    while(x)
    {
        cout << x << ":";
        for(int i=0;i<ps;i++)
            cout << pos[i] << " ";
        cout << endl;
        for(int i=0;i<ps;i++)
            ans += x*pos[i];

        num acc = 0;
        for(int i=ps-1;i>=0;i--)
            pos[i] = mod(pos[i] + pos[i+1]);
        x--;
    }
    cout << ans << endl;
}
