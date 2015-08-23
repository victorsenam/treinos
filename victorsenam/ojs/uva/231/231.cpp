#include <bits/stdc++.h>

std::vector<int> v;
std::vector<int>::iterator it;
int n;
unsigned long long int aux, t = 0;

inline bool comp (int a, int b) {
    return b < a;
}

void coloca(int n) {
    it = std::upper_bound(v.begin(), v.end(), n, comp);

    if (it == v.end()) v.push_back(n);
    else *it = n;
/*
    for (it = v.begin(); it != v.end(); it++) {
        printf("%d ", *it);
    }
    printf("\n");
*/
}

int main () {
    while (scanf("%d", &n) != EOF && n > -1) {
        if (t) printf("\n");

        coloca(n);

        while (scanf("%d", &n) != EOF && n > -1) coloca(n);
        
        printf("Test #%llu:\n  maximum possible interceptions: %u\n", ++t, v.size());
        v.clear();
    }
}
