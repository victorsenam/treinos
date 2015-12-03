#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long num;
num in;

inline num sumSquare( num x )
{
    return ((2*x+1)*x*(x+1))/6;
}

inline num squareSum( num x )
{
    num aux = (x+1)*x/2;
    return aux*aux;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> in;
    cout << squareSum(in) - sumSquare(in) << endl;
}
