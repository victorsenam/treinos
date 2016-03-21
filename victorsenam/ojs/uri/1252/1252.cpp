#include <bits/stdc++.h>

using namespace std;

const int N = 10007;

int a[N], n, m;

int main () {
    while (scanf("%d %d", &n, &m) && n && m) {
        for (int i = 0; i < n; i++)
            scanf("%d", a+i);

        for (int i = 0; i < n; i++) {
            int mini = i;
            for (int j = i+1; j < n; j++) {
                if (a[mini]%m == a[j]%m) {
                    if (a[mini]%2) {
                        if (a[j]%2 && a[j] > a[mini])
                            mini = j;
                    } else {
                        if (a[j]%2 || a[j] < a[mini])
                            mini = j;
                    }
                } else if (a[j]%m < a[mini]%m) {
                    mini = j;
                }
            }

            swap(a[mini], a[i]);
        }

        printf("%d %d\n", n, m);
        for (int i = 0; i < n; i++)
            printf("%d\n", a[i]);
    }
    printf("0 0\n");
}
