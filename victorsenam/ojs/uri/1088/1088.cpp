#include <bits/stdc++.h>

using namespace std;

#define N 100000

unsigned long long int n, v[N], p, aux;

int main () {
    while(scanf("%llu", &n) != EOF && n) {
        p = 0llu;
        for (unsigned long long int i = 0llu; i < n; i++) {
            scanf("%llu", &v[i]);
            v[i]--;
//           printf("%lu ", v[i]);
        }
//        printf("\n");

        for (unsigned long long int i = 0llu; i < n; i++) {
            if (v[i] != i) {
                if (v[i] > i) p += 2*(v[i] - i) - 1;
                else p += 2*(i - v[i]) - 1;
                p %= 2;
                    
                aux = v[v[i]];
                v[v[i]] = v[i];
                v[i] = aux;

//                printf("%llu <-> %llu : %llu \n", v[i], v[v[i]], p);

                i--;
            }
        }
        
        aux = 0llu;

        if (p%2) printf("Marcelo\n");
        else printf("Carlos\n");
    }
}
