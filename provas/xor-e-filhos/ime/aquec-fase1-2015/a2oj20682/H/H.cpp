#include <bits/stdc++.h>

using namespace std;

const bool adj[10][10] = {
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 1
    {1, 0, 1, 1, 0, 1, 1, 0, 1, 1}, // 2
    {0, 0, 0, 1, 0, 0, 1, 0, 0, 1}, // 3
    {1, 0, 0, 0, 1, 1, 1, 1, 1, 1}, // 4
    {1, 0, 0, 0, 0, 1, 1, 0, 1, 1}, // 5
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 1}, // 6
    {1, 0, 0, 0, 0, 0, 0, 1, 1, 1}, // 7
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1}, // 8
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1}  // 9
};

int t;
int k;
stack<int> st;
set<int> s;
set<int>::iterator it;

int main () {
    for (int i = 0; i <= 200; i++) {
        bool ok = 1;
        int att = 1;
        int aux = i;
        while (aux) {
            st.push(aux%10);
            aux /= 10;
        }
        while (!st.empty()) {
            if (!adj[att][st.top()])
                ok = 0;
            att = st.top();
            st.pop();
        }
        if (ok)
            s.insert(i);
    }


    scanf("%d", &t);

    while (t--) {
        scanf("%d", &k);
        int res = 4000;
        it = s.lower_bound(k);
        if (abs(k-*it) < abs(res-k))
            res = (*it);
        it--;
        if (abs(k-*it) < abs(res-k))
            res = (*it);
        it = s.upper_bound(k);
        if (it != s.end())
            if (abs(k-*it) < abs(res-k))
                res = (*it);
        printf("%d\n", res);
    }
}
