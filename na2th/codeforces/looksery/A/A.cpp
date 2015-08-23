#include <bits/stdc++.h>
#define MAX 51
using namespace std;
typedef int num;
num n,m,faces;
char in[MAX][MAX], found[26];

int main()
{
    ios::sync_with_stdio(false);
    faces = 0;
    cin >> n >> m;
    for( int i = 0; i < n; i++ )
        for( int j = 0; j < m; j++ )
            cin >> in[i][j];

    for( int i = 0; i+1 < n; i++ )
        for( int j = 0; j+1 < m; j++ )
        {
            memset( found, 0, sizeof found );
            found[ in[i][j]     - 'a' ]++;
            found[ in[i+1][j]   - 'a' ]++;
            found[ in[i][j+1]   - 'a' ]++;
            found[ in[i+1][j+1] - 'a' ]++;

            if( found['f'-'a'] == 1 &&
                found['a'-'a'] == 1 &&
                found['c'-'a'] == 1 &&
                found['e'-'a'] == 1   )
                faces++;
        }
    cout << faces << endl;

}
