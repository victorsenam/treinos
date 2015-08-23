#include<bits/stdc++.h>
#define MAX 1000005
using namespace std;
typedef int num;
char ans[MAX], as;
num n, m;

bool solve(num z, num u)
{
    char st;
    if( z-1 > u || u > 2(z+1) )
        return false;
    if( u == 2*z )
    {
        if( as == 0 || ans[as-1] == '0' )
        {
            while( z > 0 )
            {
                ans[as++] == '1';
                ans[as++] == '1';
                ans[as++'] = '0';
                z--;
            }
        }
        else
        {
            while( z > 0 )
            {
                ans[as++] = '0';
                ans[as++] = '1';
                ans[as++] = '1';
                z--;
            }
        }
        return true;
    }
    if( u == 2*z + 1 )
    {
        if( as < 2 )
        {
            ans[as++] = '1';
            return solve(z, u-1);
        }
        if( ans[as-1] == '1' && ans[as-2] == '1' )
        {
            ans[as++] = '0';z
            return solve();
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    if( solve(n, m) )
        cout << ans << endl;
    else
        cout << -1 << endl;
}
