#include <iostream>
using namespace std;

#define MOD 1000000007

int dp[19][10];
bool f[19][10];

// # of sequences ending (biggest digit) in end with length n
long long seq(int end,int n){
//cout<<"  sequence ending "<<end<<" length "<<n<<'\n';
	if(n==1)return 1;
	if(f[n][end])return dp[n][end];
	long long ret=0;
	for(int i=0;i<10;i++)
		if(i!=end)ret=(ret+seq(i,n-1))%MOD;
	f[n][end]=1;dp[n][end]=ret;
	return ret;
}

// bound: all numbers in [0, end*10^zr)
long long sp(int end,int zr,int bef){
cout<<" range ending "<<end<<" before "<<bef<<" zeroes "<<zr<<'\n';
	if(!end)return 0;
	if(!zr){
		long long ret=0;
		for(int i=0;i<end;i++)
			if(i!=bef)ret++;
		return ret;
	}
	// starts wih the null case (0)
	long long ret=1;
	// collects all starting 1-end-1
	for(int i=1;i<end;i++)
		// starts i, length zr
		for(int j=0;j<10;j++)
			if(j!=end&&j!=bef)ret=(ret+seq(j,zr))%MOD;
	// collects all between 1 to 9..zr..9
	for(int i=1;i<=zr;i++)
		// starts with 1-9
		for(int j=1;j<10;j++)
			ret=(ret+seq(j,i))%MOD;
cout<<" :"<<ret<<'\n';
	return ret;
}

long long all(int n){
	long long ret=0;
	int zr=0;
	int rev[19];
	while(n){
		rev[zr]=n%10;
		n/=10;zr++;
	}
	for(int i=0;i<zr-1;i++)
		ret=(ret+sp(rev[i],i,rev[i+1]))%MOD;
	ret=(ret+sp(rev[zr-1],zr-1,-1))%MOD;
	return ret;
}

long long bforce(int n){
	long long ret=0;
	for(int i=0;i<n;i++){
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
