#include <bits/stdc++.h>
#define SM 1004
using namespace std;
typedef unsigned long long num;
int is, ds;
char input[SM];

int main()
{
    ios::sync_with_stdio(false);
    cin >> is >> ds;

    for( int i = 0; i < is; i++ )
        cin >> input[i];

    num ans = 1;
    for( int s = 0; s + ds <= is; s++ )
    {
        num aux = 1;
        for( int d = s; d < s + ds; d++ )
            aux *= input[d] - 0x30;

        if( aux > ans )
            ans = aux;
    }
    cout << ans << endl;
}
