#include <bits/stdc++.h>

#define NM 100000

unsigned long long int inp, yes, no, aux, tyes, tno;
unsigned int n, m;

template<typename Type> Type max (Type a, Type b) {
    if (a > b) return a;
    else return b;
}

int main () {
    while (scanf("%u %u", &m, &n) != EOF && n && m) {
        tyes = tno = 0llu;

        for (int i = 0u; i < m; i++) {
            yes = no = 0llu;

            for (int j = 0u; j < n; j++) {
                scanf("%llu", &inp);

                aux = no + inp;
                no = max(no, yes);
                yes = aux;
            }

            inp = max(no, yes);

            aux = tno + inp;
            tno = max(tno, tyes);
            tyes = aux;

        }

        printf("%llu\n", max(tno, tyes));
    }
}
