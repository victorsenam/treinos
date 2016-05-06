#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3005;
ll v[N];
int n;

int main(){
	scanf("%d",&n);	
	for(int i = 0; i < n; i++) scanf("%lld",v+i);
	ll last = 1;
	int ans = 0;
	int j = 0;
	while(j < n) {
		ll sum = 0;
		while(sum < last && j < n) {
			sum += v[j++];
		}
		if(sum >= last) ans++;
		last = sum;
	}
	printf("%d\n",ans);
}
