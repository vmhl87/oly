#include <iostream>
using namespace std;

#define MOD 1000000007

int dp[19][10];
bool f[19][10];

long long seq(int n,int end){
	cout<<"running seq on "<<n<<' '<<end<<'\n';
	if(n==1)return 1;
	if(f[n][end])return dp[n][end];
	long long ret=0;
	for(int i=0;i<10;i++)
		if(i!=end)ret=(ret+seq(n-1,i))%MOD;
	f[n][end]=1;dp[n][end]=ret;
	return ret;
}

long long sp(int first,int z){
	if(!z)return first;
	long long ret=1;
	for(int i=1;i<first;i++)
		for(int j=0;j<10;j++)
			if(j!=i)ret=(ret+seq(z,j))%MOD;
	for(int i=1;i<=z;i++)
		for(int j=1;j<10;j++)
			ret=(ret+seq(i,j))%MOD;
	return ret;
}

long long all(int n){
cout<<"all on "<<n<<'\n';
	int z=0;
	long long ret=0;
	while(n){
cout<<"	segment "<<n%10<<','<<z<<'\n';
		if(n%10>0)ret=(ret+sp(n%10,z))%MOD;
		n/=10;z++;
	}
	return ret;
}

long long bforce(int n){
	long long ret=0;
	for(int i=1;i<n;i++){
		int last=-1,s=i;
		bool w=1;
		while(s){
			if(s%10==last)w=0;
			last=s%10;
			s/=10;
		}
		if(w)ret++;
	}
	return ret;
}

int main(){
	for(int i=0;i<19;i++)
		for(int j=0;j<10;j++)
			f[i][j]=0;
	int a,b;cin>>a>>b;
	long long ret=all(b+1)+MOD-all(a);
	ret%=MOD;
	cout<<ret<<'\n';
	ret=bforce(b+1)+MOD-bforce(a);
	ret%=MOD;
	cout<<ret<<'\n';
}
