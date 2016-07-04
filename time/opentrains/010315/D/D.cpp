#include <bits/stdc++.h>
using namespace std;
typedef int64_t ll;
template<typename T> inline void _max(T& a, T b){ a = max(a,b); }
template<typename T> inline void _min(T& a, T b){ a = min(a,b); }

const ll  P = 1e9+7;
const int N = 7+1e5;

struct mod{
    int x;
    mod() : x(0) {}
    mod(int a) : x(a%P) {}
    mod operator+(mod b) { return (ll(x)+ll(b.x)+P)%P; }
} S[N], A[N];

int n;
int main(){
    scanf(" %d", &n);
    S[0] = 0;
    S[1] = 1; S[2] = 2;
    for(int i=1;i<3;i++) A[i] = S[i] + A[i-1];
    for(int i=3;i<=n;i++) A[i] = A[i-1] + (S[i] = mod(1) + A[i>>1]);
    printf("%d\n", S[n].x);
}
