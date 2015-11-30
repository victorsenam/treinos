#include <bits/stdc++.h>

using namespace std;

const int N = 200007;
typedef long long int num;

int n, s;
int a[N], l[N];
int x, p;
int t;

int main () {
    scanf("%d", &n);

    num sum = 0;
    s = 1;

    for (int i = 0; i < n; i++) {
        scanf("%d", &t);

        if (t == 1) {
            scanf("%d %d", &p, &x);
            sum += p*x;
            p--;
            l[p] += x;
        } else if (t == 2) {
            scanf("%d", &x);
            a[s++] = x;
            sum += x;
        } else {
            s--;
            l[s-1] += l[s];
            sum -= a[s] + l[s];
            l[s] = 0;
        }

        printf("%.20f\n", double(sum)/double(s));
    }
}
