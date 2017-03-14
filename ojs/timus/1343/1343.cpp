#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const num MAX = 10000000ll;

int m;
num n;
num g, gen;
num pot;
bool sieve[MAX];
num primes[MAX];
num pr;

int main () {
	scanf("%d %lld", &m, &n);

	if (m == 12) {
		printf("%012lld\n", n);
		return 0;
	}

	sieve[0] = sieve[1] = 1;

	for (num i = 2; i < MAX; i++) {
		if (sieve[i]) {
			continue;
		} else {
			primes[pr++] = i;
			for (num j = 2; i*j < MAX; j++)
				sieve[j*i] = 1;
		}
	}
	
	srand(time(NULL)); rand(); rand();
	
	while (42) {
		g = 0;
		while (42) {
			gen = rand()%10;
			if (gen%2 && gen%5) {
				g += gen;
				break;
			}
		}

		pot = 10;
		for (int i = m+1; i < 12; i++) {
			gen = rand()%10;
			g += gen*pot;
			pot *= 10;
		}
		g += pot*n;
		
		for (int i = 0; i <= pr; i++) {
			if (i == pr || g < primes[i]) {
				printf("%012lld\n", g);
				return 0;
			}
			if (g%primes[i] == 0)
				break;
		}
	}
}
