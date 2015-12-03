#include <bits/stdc++.h>
using namespace std;
typedef int num;
num sol[121], in[121];

inline num sum(num n)
{ return n*(n+1)/2; }

int main()
{
    ios::sync_with_stdio(false);
    for( int i = 0; i < 120; i++ )
        cin >> in[i];

    memset(sol, 0, sizeof sol);
    for( int st = sum(14); st < sum(15); st++ )
        sol[st] = in[st];

    for( int line = 13; line >= 0; line-- )
    {
        int under = sum(line+1);

        for( int d = 0, pos = sum(line); pos < under; d++, pos++ )
            sol[pos] = in[pos] + max(sol[under+d], sol[under+d+1] );
    }
    cout << sol[0] << endl;
}
