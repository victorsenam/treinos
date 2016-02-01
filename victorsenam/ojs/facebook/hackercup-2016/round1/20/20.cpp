#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int N = 10007;

int t, ts;
int l, n, m;
num d, w[N];
num now;
multimap<num, int> wash;
multimap<num, int>::iterator it;
multiset<num> dry;
int c, el;

int main () {
    scanf("%d", &t);
    ts = 0;

    while (t--) {
        scanf("%d %d %d %lld", &l, &n, &m, &d);
        now = 0;

        for (int i = 0; i < n; i++)
            scanf("%lld", w+i);
        sort(w, w+n);

        for (int i = 0; i < min(n, l); i++, l--)
            wash.insert(make_pair(w[i], i));
        c = 0;

        while (!wash.empty() || !dry.empty()) {
            if (wash.empty() || (!dry.empty() && *(dry.begin()) < wash.begin()->first)) {
                now = *(dry.begin());
                dry.erase(dry.begin());
                m++;
            } else {
                el = wash.begin()->second;
                now = wash.begin()->first;
                wash.erase(wash.begin());

                if (l) {
                    wash.insert(make_pair(now+w[el], el));
                    l--;
                } else {
                    if (!wash.empty() && now+w[el] < wash.rbegin()->first) {
                        it = wash.end();
                        --it;
                        wash.erase(it);
                        wash.insert(make_pair(now+w[el], el));
                    }
                }

                c++;
            }

            if (c > 0 && m > 0) {
                dry.insert(now+d);
                c--; m--;
            }
            printf("%d\n", c);
        }

        printf("Case #%d: %lld\n", ++ts, now);
    }
}
