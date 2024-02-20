#include <iostream>
using namespace std;

int dp[1000001];
bool fin[1000001];

int minsteps(int n){
	if(n<10)return 1;
	if(fin[n])return dp[n];
	int best=-1;
	int t=n;
	bool dig[10];for(int i=0;i<10;i++)dig[i]=0;
	while(t){
		dig[t%10]=1;
		t/=10;
	}
	for(int i=9;i>0;i--)if(dig[i]){
		int loc=1+minsteps(n-i);
		if((best>loc||best<0)&&loc>0)best=loc;
	}
	fin[n]=1;dp[n]=best;
	return best;
}

int main(){
	for(int i=0;i<1000001;i++)fin[i]=0;
	int n;cin>>n;
	cout<<minsteps(n)<<'\n';
}
