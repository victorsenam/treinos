#include <bits/stdc++.h>
#define MAX ((int)4e6)
using namespace std;
typedef unsigned long long num;
num col[MAX], upTo;

int main()
{
    ios::sync_with_stdio(false);

    cin >> upTo;
    memset(col, -1, sizeof col);
    col[1] = 1;
    num ans = 1,
        best = 1;
    for(num n = 2; n < upTo ; n++ )
    {
        num curr = 0, aux = n;
        while( aux >= n )
        {
            if( aux%2 == 0 )
                aux /= 2;
            else
                aux = 3*aux + 1;
            curr++;
        }
        col[n] = curr + col[aux];
        if( col[n] > best )
        {
            ans = n;
            best = col[n];
        }
    }

    cout << ans << endl;
}
