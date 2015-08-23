#include <bits/stdc++.h>
using namespace std;
typedef int num;
int sz, os;
string in, out;

int main()
{
    cin >> in;
    for( int i = 0; in[i] != '\0'; i++ )
        sz++;
    cout << 26*(sz+1) - sz << endl;
}
