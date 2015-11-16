#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

num euclid (num a, num b) {
    if (a % b == 0)
        return b;
    return euclid(b, a%b);
}

int main () {
    num a, b;
    cin >> a >> b;

    int meet = 0;
    num d = euclid(a, b);

    if (a*b/d <= 0 || a*b/d > t)
        meet = 0;
    else
        

    int res = t/a + t/b - meet;
}
