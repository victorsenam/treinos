#include <bits/stdc++.h>
#define MAX 2000002
using namespace std;
typedef unsigned long long num;
char comp[MAX];

int main()
{
    ios::sync_with_stdio(false);
    int limit;
    cin >> limit;
    num ans = 0;
    memset(comp, 0, sizeof comp);
    comp[0] = comp[1] = 1;
    for( int i = 2; i <= limit; i++ )
        if( comp[i] == 0 )
        {
            ans += i;
            for( int j = 2*i; j <= limit; j += i )
                comp[j] = 1;
        }
    cout << ans << endl;
}
