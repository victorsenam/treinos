#include <bits/stdc++.h>

using namespace std;

const int N = 15;

int str[1<<N];
int inis[1<<N];
vector<int> wins[1<<N];
int n, k, t;
queue<int> q;

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &k);
        for (int i = 0; i < (1<<n); i++) {
            scanf("%d", str+i);
            inis[i] = str[i];
            q.push(i);
            wins[i].clear();
        }

        while (q.size() > 1) {
            int a = q.front();
            q.pop();
            int b = q.front();
            q.pop();
            if (b < a)
                swap(a, b);

            if (str[a] < str[b])
                swap(a, b);

            wins[a].push_back(b);
            str[a] -= str[b];
            str[a] = min(inis[a], str[a]+k);
            q.push(a);
        }

        int a = q.front();
        q.pop();
        printf("%d\n", a+1);
        for (int i = 0; i < wins[a].size(); i++) {
            if (i) printf(" ");
            printf("%d", wins[a][i]+1);
        }
        printf("\n");
    }
}
