#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

const int N = 30005;

int n, k, a;
num l[N];

void printlin (int i) {
    for (int j = 0; j < k; j++)
        printf("%d",(bool) ((1llu<<(k-j-1))&l[i]));
    printf("--> %llu\n", l[i]);
}

int main () {
    while (scanf("%d %d", &n, &k) != EOF) {
        for (int i = 0; i < n; i++) {
            l[i] = 0llu;
            for (int j =0 ; j < k; j++){ 
                scanf("%d", &a);
                
                if (a%2)
                    l[i] |= (1llu<<j);
            }
        }

        for (int i = 0; i < n; i++) {
            int maxi = i;
            for (int j = i+1; j < n; j++) {
                if (l[j] > l[maxi])
                    maxi = j;
            }

            swap(l[i], l[maxi]);

            for (int j = i+1; j < n; j++) {
                l[j] = min(l[j]^l[i], l[j]);
            }
        }

        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (l[i] != 0llu)
                cnt++;
        }
        if (cnt >= k && n > k)
            printf("N\n");
        else
            printf("S\n");
    }
}
