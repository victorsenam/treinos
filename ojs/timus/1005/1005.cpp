#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

const int N = 23;

num mask;
int w[N];
int mini;
int suma, sumb;
int n;

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", w+i);

    mini = INT_MAX;
    for (mask = 0; mask < (1llu<<n); mask++) {
        suma = sumb = 0;
        
        for (int i = 0; i < n; i++) {
            if (mask&(1llu<<i))
                suma += w[i];
            else
                sumb += w[i];
        }
        
        mini = min(mini, abs(suma-sumb));
    }
    printf("%d\n", mini);
}
