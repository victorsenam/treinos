#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

struct fulldyn {
    bool type;
    
    struct line {
        ll a, b, c;

        bool operator < (line ot) const {
            if (type)
                return a > ot.a;
            return a < ot.a;
        };
    };

    set<line> s;

    bool isUseless (set<line>::iterator it) {
        if (it == s.end())
            return true;
        set<line>::iterator pr = it, nx = next(it);

        if (it == s.begin() && nx == s.end())
            return false;
    }
} s[2];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);


}
