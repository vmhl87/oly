#include <iostream>
using namespace std;

void test_case(){
	int n,m,k,d;cin>>n>>m>>k>>d;
	int best[n];
	for(int x=0;x<n;++x){
		int h[m],dp[m];for(int i=0;i<m;++i)cin>>h[i];
		for(int i=0;i<m;++i){
			int opt=0;bool ns=1;
			for(int a=1;a<=d;++a){
				if(a>i)break;
				opt=(ns||dp[i-a]<opt?dp[i-a]:opt);
				ns=1;
			}
			dp[i]=opt+1+h[i];
		}
		best[x]=dp[m-1];
	}
	int ret=0;bool ns=1;
	int sum=0;
	for(int i=0;i<n;++i){
		sum+=best[i];
		if(i>=k){
			sum-=best[i-k];
			ret=(ns||sum<ret?sum:ret);
			ns=1;
		}
	}
	cout<<ret<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
