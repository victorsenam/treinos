#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 20;

int n;
char str[N+1], aux[N+1], inp[N+1];
ll val, att;
int s;
int len;

void increment (){
    int carry = 1;
    int i = N-1;

    while (carry) {
        aux[i] += carry;
        carry = aux[i]/10;
        aux[i] %= 10;
        i--;
    }
}

bool compare () {
    int i = 0;
    for (i = 0; i < N-1 && str[i] == aux[i]; i++);
    return str[i] >= aux[i];
}

void getnext () {
    while (true) {
        for (int i = 0; i < N; i++) {
            if (i < s)
                str[N-i-1] = inp[len-i-1];
            else
                str[N-i-1] = aux[N-i-1];
        }

        for (int i = 0; i < N; i++)
            DEBUG("%d", str[i]);
        DEBUG(" << str\n");
        
        for (int i = 0; i < N; i++)
            DEBUG("%d", aux[i]);
        DEBUG(" << aux\n");
        
        if (compare()) {
            break;
        }

        for (int i = 0; i < s; i++) {
            aux[N-i-1] = 9;
        }
        increment();
    }
    DEBUG("\n");
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf(" IAO'%s", inp);
        DEBUG("[%s]\n", inp);
        len = strlen(inp);
        
        for (int j = 0; j < len; j++)
            inp[j] -= '0';

        for (int j = 0; j < N; j++)
            aux[j] = 0;
        aux[N-1] = aux[N-3] = 9;
        aux[N-2] = 8;
        aux[N-4] = 1;

        for (s = 1; s <= len; s++) {
            getnext();
            for (int i = 0; i < N; i++)
                aux[i] = str[i];
            increment();
        }

        bool ok = 0;

        for (int i = 0; i < N; i++) {
            if (!ok && str[i] == 0)
                continue;
            ok = 1;
            printf("%d", str[i]);
        }
        printf("\n");
    }

}
