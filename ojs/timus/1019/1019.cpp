#include <bits/stdc++.h>

using namespace std;

const int MAX = 1000000000;
const int N = 10007;

int n;
int a, b, maxa, maxb, ls;
bool c;
char e;
map<int, bool> mp;
map<int, bool>::iterator it, jt, kt;

bool getColor (int i) {
    it = mp.upper_bound(i);
    it--;
    return it->second;
}

int main () {
    scanf("%d", &n);

    mp[0] = 1;
    mp[MAX] = 0;

    while (n--) {
        scanf("%d %d %c", &a, &b, &e);

        c = getColor(b);

        mp[a] = (e == 'w');
        mp[b] = c;

        it = mp.lower_bound(a);
        jt = mp.lower_bound(b);
        it++;

        while (it != jt) {
            kt = it;
            it++;
            mp.erase(kt);
        }
    }

    it = mp.begin();
    jt = mp.end();
    c = 1;
    maxa = maxb = 0;

    while (it != jt) {
        while (it != jt && !it->second)
            it++;
        if (it == mp.end())
            break;
        
        kt = it;
        while (kt != jt && kt->second)
            kt++;

        if (maxb - maxa < kt->first - it->first) {
            maxa = it->first;
            maxb = kt->first;
        }

        it = kt;
    }

    printf("%d %d\n", maxa, maxb);
}
