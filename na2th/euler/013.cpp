#include <bits/stdc++.h>
#define MAX 51
#define BASE 1000000000
char in[MAX];

using namespace std;

typedef vector<int> Int;
Int U (1,1), Z (1,0);

Int operator+(Int a, Int b)
{
    int t, ap, bp;
    long partial, carry;
    Int ans;
    ap = bp = carry = 0;
    t = min( a.size(), b.size() );

    while( ap < t )
    {
        partial = a[ap++] + b[bp++] + carry;
        ans.push_back(partial%BASE);
        carry = partial/BASE;
    }

    while( ap < a.size() )
    {
        partial = a[ap++] + carry;
        ans.push_back(partial%BASE);
        carry = partial/BASE;
    }

    while( bp < b.size() )
    {
        partial = b[bp++] + carry;
        ans.push_back(partial%BASE);
        carry = partial/BASE;
    }

    if( carry )
        ans.push_back( carry );

    return ans;
}

// Assume que *p tem uma string terminada em \0 só formada de numeros
Int str2Int(char * in)
{
    Int ans;
    int partial, 
        n = strlen(in),
        c = 0;

    while( c < n )
    {
        partial = 0;
        for(int p = 1; p < BASE && c < n; p *= 10 )
            partial += p*(in[n-1-c++] - 0x30);
        ans.push_back(partial);
    }

    return ans;
}

int main()
{
    Int ans = Z, t;
    for( int i = 0; i < 100; i++ )
    {
        for( int j = 0; j < 50; j++ )
            cin >> in[j];
        in[50] = 0;
        t = str2Int(in);
        ans = ans + t;
    }
    for( int i = ans.size()-1; i >= 0 ; i-- )
        cout << setw(9) << setfill('0') << ans[i];
    cout << endl;
}
