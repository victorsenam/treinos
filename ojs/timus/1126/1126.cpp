#include <bits/stdc++.h>

using namespace std;

int m, a;
deque<int> q;
multiset<int> s;

int main () {
    scanf("%d", &m);

    while (scanf("%d", &a) != EOF && a >= 0) {
        q.push_back(a);
        s.insert(a);

        if (q.size() == m) {
            printf("%d\n", *(s.rbegin()));
            s.erase(s.find(q.front()));
            q.pop_front();
        }
    }
}
