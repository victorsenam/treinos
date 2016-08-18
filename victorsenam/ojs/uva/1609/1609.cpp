#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1026;
typedef bitset<N> bs;

char str[N];
bs b[N], c[N], aux;
int n;
int p[N];
int r[N];
int in[N][2], is;

bool cmp_t (int i, int j) {
    return b[i].count() < b[j].count();
}

int main () {
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++) {
            scanf(" %s", str);
            int m = strlen(str);
            for (int j = 0; j < m/2; j++)
                swap(str[j], str[m-1-j]);
            c[i] = b[i] = bs(string(str));
        }

        int ps = 0;
        for (int i = 0; i < n; i++) {
            if (b[0][i]) {
                p[ps++] = i;
                DEBUG("amigo %d\n", i+1);
            }
            r[i] = -1;
        }
        sort(p, p+ps--, cmp_t);

        for (int i = 1; i < n; i++)
            b[i] &= (~b[0]);

        in[0][0] = n/2;
        in[0][1] = n;
        is = 1;
        int mini = n;

        r[0] = 0;
        for (int i = 0; i < is; i++) {
            if (in[i][0] < mini) {
                mini = in[i][0];
                in[is][0] = in[i][0] - (in[i][1] - in[i][0])/2;
                in[is][1] = in[i][0];
                is++;
            }
            if (ps >= 0 && b[p[ps]].count() >= (in[i][1] - in[i][0])) {
                r[in[i][0]] = p[ps];
                int k = 0;
                aux = 0;
                for (int j = in[i][0] + 1; j < in[i][1]; j++) {
                    while (!b[p[ps]][++k]);
                    r[j] = k;
                    aux.set(k);
                }

                for (int j = 0; j < n; j++)
                    b[j] &= (~aux);
                sort(p, p+ps--, cmp_t);
            } else {
                in[is][0] = in[i][0];
                in[is+1][1] = in[i][1];
                in[is][1] = in[is+1][0] = (in[i][0] + in[i][1])/2;
                is += 2;
            }
        }

        for (int i = 0; i < n; i++) {
            DEBUG("%d ", r[i]+1);
            if (r[i] == -1)
                r[i] = p[ps--];
        }
        DEBUG("\n");
        for (int i = 0; i < n; i++)
            DEBUG("%d ", r[i]+1);
        DEBUG("\n");
/*
        rs = 0;
        r[rs++] = 0;
        for (int i = 0; i < ps; i++) {
            sort(p+i, p+ps, cmp_t);

            r[rs++] = p[i];
            for (int j = 0; j < n; j++)
                if (b[p[i]][j])
                    r[rs++] = j;

            for (int j = i+1; j < ps; j++)
                b[p[j]] &= (~b[p[i]]);
        }
*/
        int k = 1;
        while (k < n) {
            for (int i = 0; i < n; i += k+k) {
                printf("%d %d\n", r[i]+1, r[i+k]+1);
                if (!c[r[i]][r[i+k]])
                    swap(r[i], r[i+k]);
            }
            k *= 2;
        }
    }
}
