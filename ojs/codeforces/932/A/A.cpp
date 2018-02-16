#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e3+7;
char A[N];

int main () {
	scanf(" %s", A);
	printf("%s", A);
	reverse(A,A+strlen(A));
	printf("%s\n", A);
}
