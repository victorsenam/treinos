#include <bits/stdc++.h>
using namespace std;
typedef int64_t ll;

ll solve(ll a, ll b) {
	if(a == b) return 0;
	if(b > a) swap(a, b);
	return a-a%(b+1) + solve(a%(b+1),b);
}

int a, b;
int main(){
	scanf(" %d%d", &a, &b);
	cout <<  solve(a,b) << endl;
}
