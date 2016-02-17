#include <bits/stdc++.h>
using namespace std;
typedef long long num;
const int N = 500;

int n, is, ns, ss;
num in[N*N], sol[N];
map<num, int> freq;

num gcd(num a, num b)
{ return b ? gcd(b, a%b) : a; }

int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    is = n*n;
    for(int i=0;i<is;i++) 
    {
        cin >> in[i];
        freq[in[i]]++;
    }

    while(ss < n)
    {
        num a = 0;
        for(auto it: freq)
        {
            a = max(a, it.first);
            if((it.second)&1)
            {
                a = it.first;
                break;
            }
        }
        freq[a]--;
        if(freq[a] <= 0) freq.erase(a);

        for(int i=0;i<ss;i++)
        {
            num d = gcd(a, sol[i]);
            freq[d] -= 2;
            if(freq[d] <= 0) freq.erase(d);
        }

        sol[ss++] = a;
    }

    for(int i=0;i<ss;i++)
        cout << sol[i] << " \n"[i+1==ss];
}
