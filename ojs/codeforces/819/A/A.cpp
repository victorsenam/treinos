#include <bits/stdc++.h>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug if(true)
#else
#define debug if(false)
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int a, b, l, r;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    
    cin >> a >> b >> l >> r;
    l--; r--;

    int in = (l/(a+b));
    in = max(0, in-10);

    multiset<char> del;
    set<char> s;
    queue<char> qu;
    char cur = 'a';
    bool cnt = 1;
    for (int i = in*(a+b), qt = 0; qt < 1e4 && i <= r; i++, qt++) {
        int pl = ((i%(a+b)) >= a);
        
        if (!pl) {
            while (!cnt && qu.size() > a) {
                del.erase(del.find(qu.front()));
                qu.pop();
            }
            cnt = 1;

            cur = 'a';
            while (del.find(cur) != del.end())
                cur++;
        } else {
            cnt = 0;
        }

        del.insert(cur);
        qu.push(cur);

        if (i >= l) {
            s.insert(cur);
        }
    }

    cout << s.size() << endl;
}
