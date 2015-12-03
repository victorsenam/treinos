#include <bits/stdc++.h>
#define MAX 21
using namespace std;
typedef long long num;
num ans;
int input[MAX][MAX];
int is;

int main()
{
    ios::sync_with_stdio(false);
    int aux;
    cin >> is;
    for( int i = 0; i < is*is; i++ )
        cin >> input[i/is][i%is];

    ans = 1;
    for( int i = 0; i < is; i++ )
        for( int j = 0; j < is; j++ )
        {
            num aux;
            if( i + 4 <= is )
            {
                aux = 1;
                for( int d = i; d < i + 4; d++ )
                    aux *= input[d][j];
                ans = max(ans, aux);
            }
            if( j + 4 <= is )
            {
                aux = 1;
                for( int d = j; d < j + 4; d++ )
                    aux *= input[i][d];
                ans = max(ans, aux);
            }
            if( i + 4 <= is && j + 4 <= is )
            {
                aux = 1;
                for( int d = 0; d < 4; d++ )
                    aux *= input[i+d][j+d];
                ans = max(ans, aux);
            }
            if( i + 4 <= is && j > 2 )
            {
                aux = 1;
                for( int d = 0; d < 4; d++ )
                    aux *= input[i+d][j-d];
                ans = max(ans, aux);
            }
        }
    cout << ans << endl;
}
