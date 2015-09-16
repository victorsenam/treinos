#include <bits/stdc++.h>

using namespace std;

int main () {
    printf("%d\n", 200000);

    for (int i = 0; i < 200000; i++)
        printf("%d ", (i%2)?i:-i);
}
