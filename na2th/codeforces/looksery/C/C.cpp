#include <bits/stdc++.h>
using namespace std;
typedef int num;

num oddCities, evenCities, k, n;

int main()
{
    int aux;
    ios::sync_with_stdio(false);
    cin >> n >> k;

    evenCities = 0;
    oddCities  = 0;
    for( int i = 1; i <= n; i++ )
    {
        cin >> aux;
        if( aux%2 == 1 )
            oddCities++;
        else
            evenCities++;
    }

    for( int i = 0; i < n-k; i++ )
    {
        if( evenCities == 0 )
        {
            oddCities -= n-k-i;
            break;
        }
        int par = i%2; // 0 se Stannis
                       // 1 se Daenerys

        if( i+1 < n-k )
        {
            if( oddCities%2 == par )// Estou perdendo
                evenCities--;
            else
                oddCities--;
        }
        else
        {
            if( oddCities%2 == par )
                oddCities--;
            else
                evenCities--;
        }
    }

    if( oddCities%2 == 0 )
        cout << "Daenerys" << endl;
    else
        cout << "Stannis" << endl;
}
