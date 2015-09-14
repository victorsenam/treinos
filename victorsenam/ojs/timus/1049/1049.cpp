#include <bits/stdc++.h>

using namespace std;

const int N = 10007;
int prime[N];
int res;
bool sieve[N];

int a, b;

const int n = 10;

int main () {
	for (int i = 2; i < N; i++) {
		if (sieve[i])
			continue;

		for (int j = 2; j*i < N; j++)
			sieve[i*j] = 1;
	}

	for (int i = 0; i < n; i++) {
		scanf("%d", &a);

		for (int j = 2; j <= a; j++) {
			if (!sieve[j] && a%j == 0) {
				prime[j]++;
				prime[j] %= 10;
				a /= j;
				j--;
			}
		}
	}

	res = 1;
	for (int i = 2; i < N; i++) {
		res *= (prime[i]+1);
		res %= 10;
	}

	printf("%d\n", res%10);
}
