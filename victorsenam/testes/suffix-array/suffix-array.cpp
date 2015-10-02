// http://codeforces.com/blog/entry/4025
// Suffix Array (n lg^2(n)) with LCP (n)

#include <bits/stdc++.h>

using namespace std;

const int N = 100007;

char str[N];
int sa[N];      // Suffix Array
int hk[N];      // Hank of i-th Suffix (str[i,n))
int lc[N];      // LCP
int gap;
int n;

bool suf_cmp (int i, int j) {
    if (hk[i] != hk[j])
        return hk[i] < hk[j];       // mantém a ordenação anterior
    i += gap;
    j += gap;
    if (i < n || j < n)
        return i < j;               // ultimo critério
    return hk[i] < hk[j];           // melhora a ordenação atual
}

void suffixarray () {
    n = strlen(str);

    for (int i = 0; i < n; i++) {
        sa[i] = i;
        hk[i] = sa[i];
    }

    gap = 1;
    do {
        sort(sa, sa+n, suf_cmp);

        for (int i = 0; i < n-1; i++)
            tmp[i+1] = tmp[i] + suf_cmp(sa[i], sa[i+1]);    // conta quantos items estão corretamente ordenados em sa[0,i]

        for (int i = 0; i < n; i++)
            hk[sa[i]] = tmp[i];                             // determina em que intervalo cada sa esta

        gap <<= 1;
    } while (tmp[n-1] != n-1);
}
