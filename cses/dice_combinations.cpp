#include <iostream>
using namespace std;

#define MOD 1000000007

int dp[1000001];
bool f[1000001];

int ways(int n){
	if(n==1)return 1;
	if(f[n])return dp[n];
	int ret=0;
	if(n<7)ret=1;
	for(int i=n-1;i>n-7&&i>0;i--){
		ret=(ret+ways(i))%MOD;
	}
	f[n]=1;dp[n]=ret;
	return ret;
}

int main(){
	for(int i=0;i<1000001;i++)f[i]=0;
	int n;cin>>n;
	cout<<ways(n)<<'\n';
}
