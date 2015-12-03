#include <bits/stdc++.h>
#define MAX 1001
using namespace std;
typedef int num;
num f0, f1, aux, m;
long long sum;

int main()
{
    ios::sync_with_stdio(false);
    f0 = 0; f1 = 1; sum = 0;
    cin >> m;
    while( f0 <= m )
    {
        if( f0%2 == 0 )
            sum += f0;
        aux = f1 + f0;
        f0 = f1;
        f1 = aux;
    }
    cout << sum << endl;
}
