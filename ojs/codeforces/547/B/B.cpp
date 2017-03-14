#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int N = 2e5+7;

int n;
int v[N];
int r[N][2];
int st[N], ss;
int p[N];

bool cmp_t (int i, int j) {
    return v[i] < v[j];
}

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
        p[i] = i;
    }

    for (int i = 0; i < n; i++) {
        while (ss && v[st[ss-1]] >= v[i])
            ss--;

        if (ss == 0)
            r[i][0] = i;
        else
            r[i][0] = abs(i - st[ss-1]) - 1;

        st[ss++] = i;
    }

    ss = 0;
    for (int i = n-1; i >= 0; i--) {
        while (ss && v[st[ss-1]] >= v[i])
            ss--;
        
        if (ss == 0)
            r[i][1] = n-i-1;
        else
            r[i][1] = abs(i - st[ss-1]) - 1;

        st[ss++] = i;
    }

    sort(p, p+n, cmp_t);

    int l = n-1;
    for (int s = 0; s < n; s++) {
        l++;
        int cr;
        do {
            l--;
            cr = r[p[l]][0] + r[p[l]][1] + 1;
        } while (cr <= s);
        
        printf("%d ", v[p[l]]);
    }
    printf("\n");
}
