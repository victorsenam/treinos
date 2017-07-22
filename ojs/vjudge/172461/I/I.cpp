#include <bits/stdc++.h>
#include <string>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

bool prime(ll a) {
    if(a == 1) return false;
    for(ll i = 2; i * i <= a; i++)
        if(!(a % i))
            return false;
    return true;
}


char ss[1123];
#define atoll asdsa
string atoll(ll a) {
    sprintf(ss, "%lld", a);
    return string(ss);
}

inline void solve(ll a, ll b) {
    if(a == 3 && b == 7) {
        cout << "3->5->7";
        return;
    }
    if(b == a + 2) { (cout << a << "->" << b); return; }
    if(a == 2) {
        if(prime(b - 2)) { (cout << "2->" << b); return; }
        else if(prime(b + 2)) {  (cout << "2->" << (b + 2ll) << "->" << b); return; }
        else { cout << "Unlucky Benny"; return; }
    }
    string s;
    if(prime(a - 2))
        s += string(atoll(a)) + "->2->";
    else if(prime(a + 2))
        s += string(atoll(a)) + "->" + string(atoll(a + 2ll)) + "->2->";
    else {
        cout << "Unlucky Benny";
        return;
    }

    if(prime(b - 2))
        s += string(atoll(b));
    else if(prime(b + 2))
        s += string(atoll(b + 2ll)) + "->" + string(atoll(b));
    else {
        cout << "Unlucky Benny";
        return;
    }
    
    cout << s;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll a, b;
    cin >> a >> b;
    solve(a, b);
    cout << '\n';
}
