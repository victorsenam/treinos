#include <bits/stdc++.h>
using namespace std;
typedef long long num;
num a, b;
num st, nd, guess;
num ans;

int main()
{
    cin >> a >> b;
    guess = 1;
    while(guess < num(4e18))
    {
        for(int i=0;(1ll<<(i+1))<guess;i++)
             ans += ( a <= guess-(1ll<<i) && guess-(1ll<<i) <= b);
        guess <<= 1; guess |= 1;
    }
    cout << ans << endl;
}
