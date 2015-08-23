#include <bits/stdc++.h>

using namespace std;

priority_queue<int> q;
int d, mini, t, v, n, a;

int main () {
    scanf("%d", &t);

    for (int c = 1; c <= t; c++) {
        scanf("%d", &n);

        while (!q.empty()) q.pop();
        for (int i = 0; i < n; i++) {
            scanf("%d", &v);
            q.push(v);
        }

        mini = q.top();
        for (d = 0; d < mini; d++) {
            a = q.top();
            q.pop();

            mini = min(mini, a+d);

            q.push(a/2);
            q.push(a/2 + a%2);
        }
        printf("Case #%d: %d\n", c, mini);
    }
}
