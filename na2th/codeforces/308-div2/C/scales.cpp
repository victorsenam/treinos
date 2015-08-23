#include<bits/stdc++.h>
using namespace std;
typedef int num;
num m, w, aux, k;
set<num> seen;

int main()
{
    ios::sync_with_stdio(false);
    cin >> w >> m;
    while( m != 0 )
    {
        aux = 1;
        k = 0;
        while( aux < m )
        {
            aux *= w;
            k++;
        }
        if( k > 100 || seen.count(aux) == 1 )
            break;
        else
            seen.insert(aux);
        m -= aux;
        m *= -1;
    }
    if( m == 0 )
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}
