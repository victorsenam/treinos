#include <bits/stdc++.h>

using namespace std;

map<int, int> cands;
int aux, n;
map<int, int>::iterator it, jt;

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &aux);
        it = cands.find(aux);

        if (it == cands.end() || it->first != aux) {
            cands.insert(make_pair(aux,1));
        } else {
            it->second++;
        }
    }

    it = cands.begin();

    for (jt = cands.begin(); jt != cands.end(); jt++) {
        printf("%d: %d\n", jt->first, jt->second);
        if (jt->second > it->second) it = jt;
    }

    printf("%d\n", it->first);
}
