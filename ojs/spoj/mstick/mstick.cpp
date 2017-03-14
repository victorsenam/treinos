#include <bits/stdc++.h>

using namespace std;

const int N = 10007;

int t, n;
int a;
int res;
pair<int, int> v[N];
set<int> s;
set<int>::iterator it;

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);

        s.clear();
        for (int i = 0; i < n; i++)
            scanf("%d %d", &v[i].second, &v[i].first);
        sort(v, v+n);
        
        for (int i = 0; i < n; i++) {
            a = v[i].second;
            it = s.upper_bound(a);
            if (s.empty() || it == s.begin()) {
                s.insert(a);
            } else {
                it--;
                s.erase(it);
                s.insert(a);
            }
        }
        
        printf("%d\n", s.size());
    }
}
