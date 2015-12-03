#include <bits/stdc++.h>
#define MAX 21
using namespace std;
typedef long long num;
num gridSize, ans;

int main()
{
    ios::sync_with_stdio(false);
    cin >> gridSize;
    ans = 1;

    for( num i = 1; i <= gridSize; i++ )
    {
        ans *= gridSize+i;
        if( ans < 0 )
        {
            cout << "ESTOUROU" << endl;
            break;
        }
        ans /= i;
    }

    cout << ans << endl;
}
