#include <bits/stdc++.h>

using namespace std;

int E, N, C;

int fi(int n)
{
	int res = n;
	for (int i = 2; i*i <= n; i++) 
	{
		if (n%i == 0)
		{
			res -= res/i;
			while (n%i == 0) n /= i;
		}
	}
	if (n > 1) return res -= res/n;
	else return res;
}

// sempre recebe a%C e b%C
int fexp(int a, int b)
{
	int t;
	if (b == 0) return 1;
	if (b == 1) return a;
	t = fexp(a, b/2);
	t = t%N;
	if (b%2 == 0) return (t*t)%N;
	else return (a*((t*t)%N))%N;
}

inline void copy(int *a, int *b, int size)
{
	while (size--) a[size] = b[size];
}

int main(int argc, const char *argv[])
{
	int X[3], x[3], tmp[3], d, phi, q, m;
	
	scanf("%d %d %d", &N, &E, &C);

	phi = fi(N);

	X[0] = E; X[1] = 1; X[2] = 0;
	x[0] = phi; x[1] = 0; x[2] = 1;

	while (x[0] != 0) 
	{
		q = X[0]/x[0];
		copy(tmp, X, 3);
		copy(X, x, 3);
		x[0] = tmp[0] - q*x[0];
		x[1] = tmp[1] - q*x[1];
		x[2] = tmp[2] - q*x[2];
	}

	d = X[1];
	d = ((d%phi) + phi)%phi;

	m = fexp(C%N, d);

	printf("%d\n", m);

	return 0;
}
