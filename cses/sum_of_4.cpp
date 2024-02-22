#include <iostream>
using namespace std;

typedef struct{
	int n[4];
	int c=0;
}val;

int main(){
	int n;long long x;cin>>n>>x;
	val *dp=new val[x*4+4];
	for(int r=0;r<n;r++){
		long long t;cin>>t;
		for(int i=3;i>0;i--){
			for(long long j=0;j<=x-t;j++){
				if(dp[j*4+i-1].c&&!dp[j*4+t*4+i].c){
					dp[j*4+t*4+i].c=i+1;
					for(int k=0;k<i;k++){
						dp[j*4+t*4+i].n[k]=dp[j*4+i-1].n[k];
					}
					dp[j*4+t*4+i].n[i]=r;
				}
			}
		}
		if(t<=x&&!dp[t*4].c){
			dp[t*4].n[0]=r;
			dp[t*4].c=1;
		}
	}
	if(dp[x*4+4].c){
		for(int i=0;i<4;i++){
			if(i)cout<<' ';
			cout<<dp[x*4+3].n[i]+1;
		}
		cout<<'\n';
	}else cout<<"IMPOSSIBLE\n";
}
