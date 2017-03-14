#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

num k, c, a, b, u;
int d, w;
queue<num> q;
map<num, pair<num, num> > g;
set<num> s;
bool ok;
map<num, pair<num, num> >::iterator it, jt;

bool add(num x, num y) {
    it = g.insert(pair<num, pair<num, num> >(x, pair<num, num>(y, -1))).first;
    
    if (it->second.first == y) return 1;
    if (it->second.second != -1 && it->second.second != y) return 0;
    
    it->second.second = y;
    return 1;
}

int main () {
    while (scanf("%lld %d", &k, &w) != EOF && k) {
        g.clear();
        s.clear();
        while (!q.empty()) q.pop();

        ok = 1;

        for (int i = 0; i < w; i++) {
            scanf("%lld %lld", &a, &b);
            ok = ok && add(a,b);
            ok = ok && add(b,a);
        }

        c = 0;
        for (it = g.begin(); it != g.end() && ok; it++) {
            if (s.find(it->first) != s.end()) continue;
            q.push(it->first);
            c++;
            s.insert(it->first);
            while (!q.empty()) {
                jt = g.find(q.front());
                q.pop();

                u = jt->first;
                a = jt->second.first;
                b = jt->second.second;

                d = 0;
                if (a == -1);
                else if (s.find(a) != s.end()) d++;
                else {
                    s.insert(a);
                    q.push(a);
                }
                if (b == -1);
                else if (s.find(b) != s.end()) d++;
                else {
                    s.insert(b);
                    q.push(b);
                }


                if (d >= 2 && (c > 1 || s.size() < k)) {
                    ok = 0;
                    break;
                }
            }
        }

        if (ok) printf("Y\n");
        else printf("N\n");
    }
}
