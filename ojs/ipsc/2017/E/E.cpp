#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define INF 1000000000
typedef long long ll;

int d[2123];

long long int qraise(int a){
	int resp=0;
	d[a]++;
	resp++;
	if(d[a]-d[a+1]>1){
		resp+=qraise(a+1);
	}
	if(d[a]-d[a-1]>1){
		resp+=qraise(a-1);
	}
	return resp;
}
long long int qlower(int a){
	int resp=0;
	d[a]--;
	resp++;
	if(abs(d[a]-d[a+1])>1){
		resp+=qlower(a+1);
	}
	if(abs(d[a]-d[a-1])>1){
		resp+=qlower(a-1);
	}
	return resp;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t;
	cin>>t;
	int p,e;

	while(t--){
		for(int i=0;i<2123;i++){
			d[i]=0;
		}
		int n;
		cin>>n;
		long long int resptot=0;
		for(int i=0;i<n;i++){
			cin>>p>>e;
			if(e==1){
				resptot+=qraise(p+1010)*(i+1);
			}
			else{
				resptot+=qlower(p+1010)*(i+1);
			}
			resptot=resptot%1000000009;
		}

		cout<<resptot<<"\n";


	}
	


	return 0;
}
