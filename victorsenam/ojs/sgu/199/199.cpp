#include <bits/stdc++.h>

using namespace std;

const int N = 100007;

struct peop {
    int s;
    int b;
    int ind;

    bool operator < (peop a) {
        if (s != a.s) return s < a.s;
        return b > a.b;
    }
};

int n;
int rs, ps;
peop aux;
peop v[N];
int last[N];
int lis[N];
int res[N];
stack<int> st;

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &v[i].s, &v[i].b);
        v[i].ind = i;
    }

    rs = 0;
    int toP = -1;

    sort(v, v+n);

    for (int i = 0; i < n; i++) {
        ps = lower_bound(lis, lis+rs, v[i].b) - lis;
        lis[ps] = v[i].b;
        res[ps] = v[i].ind;
        if (ps)
            last[v[i].ind] = res[ps-1];
        else
            last[v[i].ind] = -1;
        if (ps == rs) {
            toP = v[i].ind;
            rs++;
        }
    }


    printf("%d\n", rs);
    while (toP != -1) {
        st.push(toP);
        toP = last[toP];
    }

    while (!st.empty()) {
        printf("%d", st.top()+1);
        if (st.size() != 1) printf(" ");
        st.pop();
    }
}
