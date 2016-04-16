#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 1007;

int t;
char str[N];
deque<char> dq;

int main () {
    scanf("%d", &t);
    for (int ts = 1; ts <= t; ts++) {
        while (!dq.empty()) dq.pop_back();

        scanf(" %s", str);

        int n = strlen(str);
        dq.push_back(str[0]);
        for (int i = 1; i < n; i++) {
            if (str[i] >= dq.front())
                dq.push_front(str[i]);
            else
                dq.push_back(str[i]);
        }

        printf("Case #%d: ", ts);
        while (!dq.empty()) {
            printf("%c", dq.front());
            dq.pop_front();
        }
        printf("\n");
    }
}
