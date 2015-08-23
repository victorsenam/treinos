#include <bits/stdc++.h>

using namespace std;

#define L 10002

struct quatern {
    char v;
    bool s;
};

char mul[4][4] = { {'h', 'i', 'j', 'k'}, {'i', 'h', 'k', 'j'}, {'j', 'k', 'h', 'i'}, {'k', 'j', 'i', 'h'} };
bool sig[4][4] = { {0, 0, 0, 0}, {0, 1, 0, 1}, {0, 1, 1, 0}, {0, 0, 1, 1} };

inline quatern inc(quatern a, quatern b) {
    quatern c;
    c.v = mul[a.v-'h'][b.v-'h'];
    c.s = (a.s+b.s+sig[a.v-'h'][b.v-'h'])%2;
    return c;
}

quatern remd(quatern a, quatern b) { // c*b = a
    int i;
    quatern c;
    for (i = 0; i < 4; i++) {
        if (mul[i][b.v-'h'] == a.v) {
            c.v = i+'h';
            c.s = (a.s + b.s + sig[i][b.v-'h'])%2;
        }
    }
    return c;
}
quatern reme(quatern a, quatern b) { // b*c = a
    int i;
    quatern c;
    for (i = 0; i < 4; i++) {
        if (mul[b.v-'h'][i] == a.v) {
            c.v = i+'h';
            c.s = (a.s + b.s + sig[b.v-'h'][i])%2;
        }
    }
    return c;
}
void printState(int i, int j, quatern lo, quatern mid, quatern hi) {
    printf("(%d,%d) -> ", i, j);
    if (lo.s) printf("-");
    printf("%c ", lo.v);
    if (mid.s) printf("-");
    printf("%c ", mid.v);
    if (hi.s) printf("-");
    printf("%c ", hi.v);
    printf("\n");
}

int main () {
    unsigned long long x, l, i, j, n;
    quatern s[L], lo, mid, hi, tot;
    char temp;
    int t;

    scanf("%d", &t);
    for (int c = 1; c <= t; c++) {
        scanf("%llu %llu", &l, &x);

        i = 0;
        n = j = l*x;
        lo.v = mid.v = hi.v = 'h';
        lo.s = mid.s = hi.s = 0;

        for (int k = 0; k < l; k++) {
            scanf(" %c", &temp);
            s[k].v = temp;
            s[k].s = 0;
            mid = inc(mid, s[k]);
        }
        
        tot = mid;

        // exp log
        while (x > 1) {
            if (x % 2) {
                mid = inc(mid, tot);
                x--;
            } else {
                mid = inc(mid, mid);
                x /= 2;
            }
        }

        tot = mid;

        lo.v = 'h';
        lo.s = 0;
        bool ok = 0;
        i = 0;
// ao inves disso, ver se i*j*k = tot
        while (i < n && !ok) {
            lo = inc(lo, s[i%l]);
            tot = reme(tot, s[i%l]);
            i++;

            if (lo.v != 'i' || lo.s) continue;

// checa se é possivel achar um mid = j com esse lo
            hi.v = 'k';
            hi.s = 0;
            mid = remd(tot, hi);
 //           printf("%llu %d%c %d%c\n", i, lo.s, lo.v, mid.s, mid.v);


            if (mid.v != 'j' || mid.s) continue;

            mid = tot;
            hi.v = 'h';
            hi.s = 0;
            j = n;
            while (j > i) {
                j--;
                hi = inc(s[j%l], hi);
                if (hi.v == 'k' && !hi.s) {
                    //printState(i, j, lo, mid, hi);
                    ok = 1;
                    break;
                }
            }
        }

        printf("Case #%d: ", c);
        if (ok) printf("YES");
        else printf("NO");
        printf("\n");
    }
}
