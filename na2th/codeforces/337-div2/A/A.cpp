#include <bits/stdc++.h>
using namespace std;
typedef long long num;
typedef int node;
typedef int edge;

num n;
int main()
{
    cin >> n;
    if(n&1)
        cout << 0 << endl;
    else
        cout << (n/2-num(1))/2 << endl;
}
