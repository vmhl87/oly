#include <iostream>
using namespace std;

int main(){
	int k,m,n;cin>>k>>m>>n;
	bool dp[k+1];
	dp[0]=0;
	for(int i=1;i<=k;++i){
		if(i<m&&i<n){
			dp[i]=0;
			continue;
		}
		if((i<m||dp[i-m])&&(i<n||dp[i-n]))
			dp[i]=0;
		else dp[i]=1;
	}
	for(int i=0;i<=k;++i){
		cout<<i<<"  ";
		if(dp[i])cout<<"A\n";
		else cout<<"B\n";
	}
}
