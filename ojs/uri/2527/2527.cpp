#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 6001;

double memo[N][N];
int n, v;

int main () {
	memo[0][0] = 1;

	for (int i = 1; i < N; i++) {
		for (int j = 1; j < N; j++) {
			for (int k = 1; k <= 6 && j - k >= 0; k++)
				memo[i][j] += memo[i-1][j-k]/6;
		}
	}

	for (int i = 1; i < N; i++)
		for (int j = N-2; j >= 0; j--)
			memo[i][j] += memo[i][j+1];

	while (scanf("%d %d", &n,&v) != EOF)
		printf("%.4f\n", memo[n][v]);
}
