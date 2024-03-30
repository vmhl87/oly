#include <iostream>
#include <vector>
using namespace std;

#define M 1000000007

vector<int> coins;

long long dp[1000001];
bool fin[1000001];
long long ways(int s){
	if(s==0)return 1;
	if(fin[s])return dp[s];
	long long ret=0;
	for(int i:coins)if(s>=i)
		ret=(ret+ways(s-i))%M;
	fin[s]=1;dp[s]=ret;
	return ret;
}

int main(){
	int n,x;cin>>n>>x;
	coins.resize(n);
	for(int i=0;i<n;++i)cin>>coins[i];
	cout<<ways(x)<<'\n';
}
