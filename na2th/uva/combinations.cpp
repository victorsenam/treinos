#include<bits/stdc++.h>
using namespace std;
typedef long long num;
num in, im, sol[102][102];
const num MOD = (1ll<<61)-1;

inline num mod(num x)
{ return (x%MOD + MOD)%MOD; }

int main()
{
    sol[0][0] = 1ll;
    for(int i=1;i<101;i++)
        sol[i][0] = 1ll;
    for(int i=1;i<101;i++)
        for(int j=0;j<i+1;j++)
            sol[i][j] = mod(sol[i-1][j-1] + sol[i-1][j]);
    while(cin >> in >> im)
        if( in && im )
            cout << in << " things taken " << im << " at a time is "<< mod(sol[in][im]) << " exactly." << endl;
        else break;
}
