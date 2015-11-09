#include <bits/stdc++.h>

using namespace std;
typedef long long int num;

const int N = 100007;

int n, aux;
num ini, fim;
num k[N], b[N];
num s[N], e[N];
multiset<num> fins;
multiset<num>::iterator it;
int p[N];

bool my_cmp(int i, int j) {
    if (s[i] != s[j])
        return s[i] < s[j];
    return e[i] < e[j];
}

void succ () {
    printf("Yes\n");
    exit(0);
}

int main () {
    scanf("%d", &n);

    scanf("%lld %lld", &ini, &fim);

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", k+i, b+i);

        s[i] = k[i]*ini + b[i];
        e[i] = k[i]*fim + b[i];
        p[i] = i;
        fins.insert(e[i]);
    }

    sort(p, p+n, my_cmp);

    for (int i = 0; i < n; i++) {
        int j = p[i];
        printf("%lld %lld\n", s[j], e[j]);

        num bal = *(fins.begin());

        if (bal < e[j]) {
            succ();
        }
        fins.erase(fins.find(e[j]));
    }
    printf("No\n");
}
