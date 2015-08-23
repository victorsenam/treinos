#include <bits/stdc++.h>

using namespace std;

typedef unsigned int num;
vector<num> grd;
vector<num>::iterator it;
num n, k, p, x, y, a;
num qtdMins, qtdMeds;
num sum, pos;

int main() {
    scanf("%u %u %u %u %u", &n, &k, &p, &x, &y);

    qtdMins = qtdMeds = sum = 0;
    bool ismed = 0;
    for (int i =0; i < k; i++) {
        scanf("%u", &a);
        if (a == y) ismed = 1;
        sum += a;
        grd.push_back(a);
    }

    sort(grd.begin(), grd.end());

    it = lower_bound(grd.begin(), grd.end(), y);
    pos = it - grd.begin();
    
    if (n/2 - pos > n-k) qtdMins = n - k;
    else qtdMins = n/2 - pos;

    qtdMeds = n - k - qtdMins;

    sum += qtdMins + qtdMeds*y;

    if (pos > n/2 || sum > x) printf("-1\n");
    else {
        for (int i = 0; i < qtdMins; i++) {
            if (i) printf(" ");
            printf("1");
        }
        if (qtdMins) printf(" ");
        for (int i = 0; i < qtdMeds; i++) {
            if (i) printf(" ");
            printf("%u", y);
        }
        printf("\n");
    }
}
