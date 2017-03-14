#include <bits/stdc++.h>

using namespace std;

int a, b, ta, tb, aux;
vector<int> ca, cb;

int main () {
    while (scanf("%d %d", &a, &b) != EOF && a && b) {
        ca.clear();
        cb.clear();

        for (int i = 0; i < a; i++) {
            scanf("%d", &aux);
            ca.push_back(aux);
        }
        sort(ca.begin(), ca.end());
        for (int i = 0; i < b; i++) {
            scanf("%d", &aux);
            cb.push_back(aux);
        }
        sort(cb.begin(), cb.end());

        ta = tb = 0;

        for (int i = 0; i < a; i++) {
            if (i && ca[i] == ca[i-1]) continue;
            if (binary_search(cb.begin(), cb.end(), ca[i])) continue;
            ta++;
        }
        for (int i = 0; i < b; i++) {
            if (i && cb[i] == cb[i-1]) continue;
            if (binary_search(ca.begin(), ca.end(), cb[i])) continue;
            tb++;
        }

        printf("%d\n", min(ta, tb));
    }
}
