#include <bits/stdc++.h>
#define MAX 1001
using namespace std;
typedef int num;
num mult[MAX], sum, m;

int main()
{
    ios::sync_with_stdio(false);
    cin >> m;
    m++;
    memset(mult, 0, sizeof mult);
    for( int i = 3; i < m; i+= 3 )
        mult[i] = 1;
    for( int i = 5; i < m; i+= 5)
        mult[i] = 1;
    sum = 0;
    for( int i = 0; i < m; i++ )
        if( mult[i] )
            sum += i;
    cout << sum << endl;

}
