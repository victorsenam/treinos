#include <bits/stdc++.h>

using namespace std;

int n, k;
queue<int> q;
int t;

int main () {
    scanf("%d %d", &n, &k);

    int res = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &t);

        while (!q.empty() && q.front() <= t)
            q.pop();

        q.push(t+1000);

        res = max(res, (int)q.size());
    }
    printf("%d\n", (res+k-1)/k);
}
