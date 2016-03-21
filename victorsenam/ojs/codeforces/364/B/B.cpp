#include <bits/stdc++.h>

using namespace std;

const int N = 57;
const int K = 600007;

int n, d;
int c[N];

int tim[K];
int qtd[K];
multiset<int> s;

int main () {
    scanf("%d %d", &n, &d);

    for (int i = 0; i < n; i++)
        scanf("%d", c+i);

    qtd[0] = -1;
    tim[0] = 0;
    s.insert(0);

    for (int i = 1; i < K; i++) {
        if (i-d-1 >= 0 && tim[i-d-1] != -1)
            s.erase(s.find(tim[i-d-1]));
        if (s.empty()) {
            printf("%d %d\n", i-d-1, tim[i-d-1]);
            return 0;
        }

        qtd[i] = n;
        for (int j = n-1; j >= 0; j--) {
            if (i >= c[j] && qtd[i-c[j]] < j)
                qtd[i] = j;
        }

        if (qtd[i] == n) {
            tim[i] = -1;
        } else {
            tim[i] = *(s.begin()) + 1;
            s.insert(tim[i]);
        }
    }
}
