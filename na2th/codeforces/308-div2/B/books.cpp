#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int num;
num n, aux, k, ans;

int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    k = 1; aux = 1;
    while( 10*aux <= n )
    {
        ans += 9*aux*k;
        aux *= 10;
        k++;
    }
    if( 10*aux != n )
        ans += (n+1-aux)*k;
    cout << ans << endl;
    
}
