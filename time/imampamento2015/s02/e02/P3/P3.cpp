#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

#define N 103

int n, v[N];
num cnt;
vector<int> pri, sec;

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", v+i);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                pri.push_back(v[i]*v[j]+v[k]);
                if (v[k] != 0)
                    sec.push_back((v[i]+v[j])*v[k]);
            }
        }
    }

    sort(pri.begin(), pri.end());
    sort(sec.begin(), sec.end());
    
    num i = 0, j = 0, ci, cj;
    cnt = 0;
    while (i < pri.size() && j < sec.size()) {
        if (pri[i] == sec[j]) {
            ci = 0;
            cj = 0;
            while (pri[ci+i] == pri[i])
                ci++;
            while (sec[cj+j] == sec[j])
                cj++;

            cnt += ci*cj;
            i += ci;
            j += cj;
        } else if (pri[i] > sec[j])
            j++;
        else
            i++;
    }

    printf("%llu\n", cnt);
}
