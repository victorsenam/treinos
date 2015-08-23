#include <bits/stdc++.h>
#define MAX 110
using namespace std;
typedef int num;
num mat[MAX][MAX], igor[MAX], sum[MAX], n, chosen[MAX], cs;

bool possible( int p )
{
    bool foi;

    // Chegou no final
    if( p == n )
    {
        // Checa se foi
        foi = true;
        for( int i = 0; foi && i < n; i++ )
            foi = foi && (sum[i] != igor[i]);

        return foi;
    }

    // Coloca
    for( int i = 0; i < n; i++ )
        sum[i] += mat[p][i];
    chosen[cs++] = p+1;

    // Tenta com
    if( possible(p+1) ) return true;

    // Tira
    for( int i = 0; i < n; i++ )
        sum[i] -= mat[p][i];
    cs--;

    // Tenta sem
    if ( possible( p+1 ) ) return true;
}

int main()
{
    ios::sync_with_stdio(false);
    char aux;
    cin >> n;
    for( int i = 0; i < n; i++ )
        for( int j = 0; j < n; j++ )
        {
            cin >> aux;
            mat[i][j] = aux - 0x30;
        }
    for( int i = 0; i < n; i++ )
        cin >> igor[i];

    memset(sum,0, sizeof sum);
    cs = 0;

    if( possible(0) )
    {
        cout << cs << endl;
        for( int i = 0; i < cs; i++ )
            cout << chosen[i] << " ";
        cout << endl;
    }
    else
        cout << -1 << endl;
}
