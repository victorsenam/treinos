#include<bits/stdc++.h>
#define MAX 6008
using namespace std;
typedef int num;
num n, f[MAX], ans, m;

int main()
{
    num aux;
    memset(f, 0, sizeof f);
    ans = 0;
    m = -1;

    cin >> n;
    for( int i = 0; i < n; i++ )
    {
        cin >> aux;
        m = max(m, aux);
        f[aux]++;
    }

    bool over = false;
    for( int i = 1; !over ; i++ )
    {
        if( f[i] > 1 )
        {
            // Promovo e pago por eles
            ans += f[i] -1;
            f[i+1] += f[i] - 1;
            f[i] = 1;
        }
        else if( i > n )
            over = true;
    }

    cout << ans << endl;
}
