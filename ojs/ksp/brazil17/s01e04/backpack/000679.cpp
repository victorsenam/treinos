#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <assert.h>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <utility>
#include <string.h>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <complex>

#define inf (1LL<<50)
#define pii pair<int,int>
#define pip pair<int,pii>
#define pll pair<long long,long long>
#define pif pair<int,double>
#define pdp pair<double,pii>
#define eps 1e-7

#ifdef ONLINE_JUDGE
#define debug(args...)
#else
#define debug(args...) //fprintf(stderr,args)
#endif

#define pb push_back
#define maxn 3000300

#define mod 1000000007

typedef long long ll;
using namespace std;


int last[22][maxn];
int cur = 0;

int dp[22][maxn];

char v[6][maxn];

int f[6][maxn];
int ans[maxn];
int dzt[6][maxn];

int get(int id,int pos,int mask){
	if(pos == 22){
		if(v[id][mask] == '1')
			return 1;
		else
			return 0;
	}
	if(last[pos][mask] == cur)
		return dp[pos][mask];
	last[pos][mask] = cur;

	int ret = get(id,pos+1,mask);
	if(mask & (1<<pos))
		ret += get(id,pos+1,mask^(1<<pos));
	return dp[pos][mask] = ret;
}

int get2(int id,int pos,int mask){
	if(pos == 22){
		if(__builtin_popcount(mask) & 1)
			return f[id][mask];
		else
			return -f[id][mask];
	}
	debug("get2 %d %d %d\n",id,pos,mask);
	if(last[pos][mask] == cur)
		return dp[pos][mask];
	last[pos][mask] = cur;
	int ret = get2(id,pos+1,mask);
	if(mask & (1<<pos))
		ret += get2(id,pos+1,mask^(1<<pos));
	return dp[pos][mask] = ret;
}

main(){

	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);

	int n,k,q;
	scanf("%d%d%d",&n,&k,&q);
	
	for(int i=0;i<k;i++)
		scanf(" %s",v[i]);	
	
	for(int i=0;i<k;i++){
		cur++;
		for(int j=0;j<(1<<n);j++){
			dzt[i][j] = get(i,0,j);
			debug("dzt[%d][%d] = %d\n",i,j,dzt[i][j]);
		}
	}
	
	debug("ok\n");
	
	for(int i=0;i<q;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		for(int j=0;j<(1<<n);j++)
			f[i][j] = dzt[a][j] * dzt[b][j];
	}
	
	cout << "ok";
	
	for(int i=0;i<q;i++){
		cur++;
		for(int j=0;j<(1<<n);j++){
			ans[j] = get2(i,0,j);
			if(ans[j]) printf("1");
			else printf("0");
		}
		printf("\n");
	}
	
}
