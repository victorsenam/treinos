#include <bits/stdc++.h>

using namespace std;

const int N = 1000007;
typedef unsigned long long int num;

int n;
int a[N];
num sum[N];

num solve (int i, int j) {
	if (i >= j)
		return 0;
	if (j == i+1)
		return sum[j] - sum[i];
	
	return sum[j] - sum[i] + solve(i, i+(j-i)/2) + solve(i+(j-i)/2, j);
}

int main () {
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++)
		scanf("%d", a+i);
	sort(a, a+n);

	sum[0] = 0;
	for (int i = 1; i <= n; i++)
		sum[i] = sum[i-1] + a[i-1];

	printf("%llu\n", solve(0, n));
}
