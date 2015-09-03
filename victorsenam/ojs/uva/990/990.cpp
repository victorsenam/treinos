#include <bits/stdc++.h>

using namespace std;

const int N = 37;
const int T = 1007;

int memo[N][T];
bool nx[N][T];
int n, t, w;
int d[N], v[N];
vector<int> st;

int getSol (int i, int t) {
    if (i == n)
        return 0;

    if (nx[i][t]) {
        st.push_back(i);
        return getSol(i+1, t-w*3*d[i]) + 1;
    } else {
        return getSol(i+1, t);
    }
}

int pd (int i, int t) {
    if (i == n)
        return 0;

    int & m = memo[i][t];

    if (m != -1)
        return m;

    m = pd(i+1, t);
    if (w*3*d[i] <= t) {
        int aux = pd(i+1, t-w*3*d[i]) + v[i];
        if (m < aux) {
            m = aux;
            nx[i][t] = 1;
        }
    }

    return m;
}

int main () {
    bool ok = 0;
    while (scanf("%d %d", &t, &w) != EOF) {
        scanf("%d", &n);

        for (int i = 0; i < n; i++)
            scanf("%d %d", d+i, v+i);

        memset(memo, -1, sizeof memo);

        if (ok)
            printf("\n");
        else
            ok = 1;
        printf("%d\n", pd(0, t));

        st.clear();
        printf("%d\n", getSol(0, t));

        for (int i = 0; i < st.size(); i++)
            printf("%d %d\n", d[st[i]], v[st[i]]);
    }
}
