#include <bits/stdc++.h>
using namespace std;
typedef long long num;
typedef int node;
typedef int edge;

const int N = 2e5+5;
num n, c[N], m;
num sol[N];

int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    m = 1e9;
    for(int i=0; i<n;i++)
    {
        cin >> c[i];
        m = min(m, c[i]);
    }
    for(int i=0;i<n;i++)
        c[i] -= m;
    for(int i=1;i<n;i++)
        sol[i] = (c[i] > 0)*sol[i-1] + (c[i] > 0);
    sol[0] = (c[0] > 0)*sol[n-1] + (c[0] > 0);
    int p = 1;
    while(c[p] != 0)
    {
        sol[p] = sol[p-1] + 1;
        p++;
    }
    cout << m*n + *max_element(sol, sol+n) << endl;
}
