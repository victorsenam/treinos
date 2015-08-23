#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%d| ", __LINE__); fprintf(stderr, __VA_ARGS__)
#else
#define debug(...) //
#endif

#define N 

using namespace std;

typedef int num;

int n, a, b, k, fat;
queue<int> qa;
queue<int> qb;

int main () {
    scanf("%d", &n);
    fat = 1;

    scanf("%d", &a);
    for (int i = 0; i < a; i++) {
        fat *= i+1;
        scanf("%d", &k);
        qa.push(k);
    }

    scanf("%d", &b);
    for (int i = 0; i < b; i++) {
        fat *= i+1+a;
        scanf("%d", &k);
        qb.push(k);
    }

    for (int i = 0; i < fat*n; i++) {
        if (qa.empty()) {
            printf("%d 2\n", i);
            return 0;
        } else if (qb.empty()) {
            printf("%d 1\n", i);
            return 0;
        } else {
            if (qa.front() > qb.front()) {
                qa.push(qb.front());
                qa.push(qa.front());
            } else {
                qb.push(qa.front());
                qb.push(qb.front());
            }
            qa.pop();
            qb.pop();
        }
    }
    printf("-1\n");
}
