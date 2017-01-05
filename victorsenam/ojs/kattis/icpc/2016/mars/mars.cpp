#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int N = 23;

int res[N];
int pri[N];
int ans[N];
int n, r;

struct inst {
    char c;
    int t;
};

struct task {
    deque<inst> w;
    bool block;
    int start;
    int base;
    int curr;
};

task v[N];

int main () {
    scanf("%d %d", &n, &r);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i].start);
        scanf("%d", &v[i].base);

        int k;
        scanf("%d", &k);
        for (int j = 0; j < k; j++) {
            inst aux;
            scanf(" %c%d", &aux.c, &aux.t);

            if (aux.c == 'L')
                pri[aux.t] = max(pri[aux.t], v[i].base);

            v[i].w.push_back(aux);
        }
    }

    int fin = 0;
    int cloc = 0;

    while (fin < n) {
        for (int i = 1; i <= n; i++) {
            v[i].block = 0;
            v[i].curr = v[i].base;
        }

        int maxi;
        while (true) {
            maxi = 0;
            for (int i = 1; i <= n; i++) {
                if (v[i].block) continue;
                if (v[i].start > cloc) continue;
                if (v[i].w.empty()) continue;
                if (maxi == 0 || v[maxi].block || v[i].curr > v[maxi].curr)
                    maxi = i;
            }
            if (maxi == 0) break;
            int i = maxi;

            if (v[i].w.front().c == 'L') {
                for (int j = 1; j <= r; j++) {
                    if (res[j] != 0 && res[j] != i && pri[j] >= v[i].curr) {
                        v[i].block = 1;
                        v[res[j]].curr = max(v[res[j]].curr, v[i].curr);
                    }
                }

                if (res[v[i].w.front().t] != 0) {
                    v[i].block = 1;
                    v[res[v[i].w.front().t]].curr = max(v[res[v[i].w.front().t]].curr, v[i].curr);
                }
            }

            if (!v[maxi].block)
                break;
        }

        if (maxi == 0) {
            cloc++;
            continue;
        }
        
        int k = maxi;
        if (v[k].w.empty()) {
            ans[k] = cloc;
        } else {
            inst aux = v[k].w.front();
            v[k].w.pop_front();

            if (aux.c == 'L')
                res[aux.t] = k;
            else if (aux.c == 'U')
                res[aux.t] = 0;
            else {
                aux.t--;
                if (aux.t > 0)
                    v[k].w.push_front(aux);
                cloc++;   
            }

            if (v[k].w.empty()) {
                ans[k] = cloc;
                fin++;
            }
        }
    }

    for (int i = 1; i <= n; i++)
        printf("%d\n", ans[i]);
}
