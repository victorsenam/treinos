#include <bits/stdc++.h>

using namespace std;

const int N = 40007;

int m, n;
char str[N];
int hk[N];
int tmp[N];
int gap;
int sa[N];

bool sa_cmp (int i, int j) {
    if (hk[i] != hk[j])
        return hk[i] < hk[j];

    i += gap;
    j += gap;
    if (i >= n || j >= n)
        return i < j;
    return str[i] < str[j];
}

int main () {
    while (scanf("%d", &m) != EOF && m) {
        scanf(" %s", str);

        n = strlen(str);
        
        do {
            sort(sa, sa+n, sa_cmp);
            gap <<= 1;

            for (int i = 1; i < n; i++)
                tmp[i] = tmp[i-1] + (hk[sa[i]] != hk[sa[i-1]]);
            for (int i = 1; i < n; i++)

                
        } while (tmp[n-1] != n-1);
    }
}
