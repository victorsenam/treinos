#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define all(a) a.begin(), a.end()
using namespace std;
typedef long long num;

num l, r, k, c;
int flag = 0;
int main()
{
    ios::sync_with_stdio(false);
    cin >> l >> r >> k;
    c = 1;
    while(0 < c && c <= r)
    {
        if(c >= l)
        {
            cout << c << " ";
            flag = 1;
        }
        c *= k;
    }
    if(!flag) cout << "-1" ;
    cout << endl;
}
