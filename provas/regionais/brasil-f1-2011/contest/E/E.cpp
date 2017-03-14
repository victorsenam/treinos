#include <bits/stdc++.h>

using namespace std;
#define T 1000

int t, n;
int p, q;
char c;
int vac[T];
int lv;
int res;
map<int, int> posis;

void clearCar(int i, int pl) {
    while (i < t && vac[i] == pl) {
        vac[i] = 0;
        i++;
    }
}

void putCar(int ini, int pl, int siz) {
    for (int i = ini; i < ini + siz; i++)
        vac[i] = pl;
}

int main () {
    while (scanf("%d %d", &t, &n) != EOF) {
        res = 0;
        for (int i = 0; i < t; i++)
            vac[i] = 0;
        posis.clear();
        
        for (int l = 0; l < n; l++) {
            scanf(" %c %d", &c, &p);
            lv = -1;
            if (c == 'C') {
                scanf("%d", &q);
                for (int i = 0; i < t; i++) {
                    if (vac[i] != 0) lv = i;
                    if (i - lv == q) {
                        putCar(lv + 1, p, q);
                        posis.insert(make_pair(p, lv+1));
                        res++;
                        break;
                    }
                }
            } else {
                clearCar(posis.find(p)->second, p);
                posis.erase(p);
            }
        }

        printf("%d\n", res*10);
    }
}
