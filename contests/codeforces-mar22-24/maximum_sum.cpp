#include <iostream>
using namespace std;

#define M 1000000007

void test_case(){
	int n,k;cin>>n>>k;
	long long a[n];for(int i=0;i<n;++i)cin>>a[i];
	long long tsum=0;
	for(int i=0;i<n;++i)tsum=(tsum+a[i])%M;
	if(tsum<0)tsum+=M;
	long long max=0,best=0;
	for(int i=0;i<n;++i){
		if(max<0)max=0;
		max+=a[i];
		if(max>best)best=max;
	}
	best%=M;
	if(best<0)best+=M;
	for(int i=0;i<k;++i){
		tsum=(tsum+best)%M;
		best=(best*2)%M;
	}
	cout<<tsum<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
