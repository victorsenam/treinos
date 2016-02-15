#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 307;

int n;
int a[N];
int pre[N], pos[N];
int from[N], freq[N];
int cnt;
int t;

int main () {
    scanf("%d %d", &n, &t);

    for (int i = 0;  i< n ; i++) {
        scanf("%d", a+i);
        freq[a[i]]++;
    }

    cnt = 0;
    for (int i = 0; i < n; i++) {
        pre[i] = 1;
        from[i] = a[i];
        for (int j = 0; j < i; j++) {
            if (a[j] >= a[i] && pre[j] + 1 > pre[i]) {
                pre[i] = pre[j] + 1;
                from[i] = a[j];
            }
        }
        cnt += (from[i] == a[i]);
    }
    t--;
    while (cnt < n && t > 1) {
        t--;
        cnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[j] >= a[i] && pre[j] + 1 > pre[i]) {
                    pre[i] = pre[j] + 1;
                    from[i] = a[j];
                }
            }
            cnt += (from[i] == a[i]);
        }
    }

    if (!t) {
        int maxi = 0;
        for (int i = 0; i < n; i++) {
            maxi = max(maxi, pre[i]);
        }
        printf("%d\n", maxi);
        return 0;
    }
    cnt = 0;
    for (int i = n-1; i >= 0; i--) {
        pos[i] = 1;
        from[i] = a[i];
        for (int j = i+1; j < n; j++) {
            if (a[i] <= a[j] && pos[j] + 1 > pos[i]) {
                pos[i] = pos[j] + 1;
                from[i] = a[j];
            }
        }
        cnt += (from[i] == a[i]);
    }
    t--;

    while (cnt < n && t > 1) {
        t--;
        cnt = 0;
        for (int i = n-1; i >= 0; i--) {
            for (int j = 0; j < n; j++) {
                if (a[i] <= a[j] && pos[j] + 1 > pos[i]) {
                    pos[i] = pos[j] + 1;
                    from[i] = a[j];
                }
            }
            cnt += (from[i] == a[i]);
        }
    }

    int maxi = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = a[i]; k <= a[j]; k++)
                maxi = max(maxi, pre[i] + pos[j] + freq[k]*t);

    printf("%d\n", maxi);
}
