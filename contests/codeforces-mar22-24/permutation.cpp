#include <algorithm>
#include <iostream>
using namespace std;

#define M 1000000007

long long dp[200001];
bool f[200001];
long long fact(long long n){
	if(f[n])return dp[n];
	long long ret=1;
	for(long long i=n;i>1;--i)ret=(ret*i)%M;
	f[n]=1;dp[n]=ret;
	return ret;
}

long long inv(long long a,long long p){
	long long p2=1,iter=0,pn=p-2;
	long long pa=a,ret=1;
	while(p2<pn){
		if(pn&(1<<iter))ret=(ret*pa)%p;
		pa=(pa*pa)%p;
		p2<<=1;iter++;
	}
	return ret;
}

long long nck(long long n,long long k){
	long long num=fact(n),den=fact(k);
	den=(den*fact(n-k))%M;
	den=inv(den,M);
	return (num*den)%M;
}

long long choose(long long n,long long k){
	if(k>n)return choose(k,n);
	return nck(n,min(k,n-k));
}

void test_case(){
	long long n,p,s;cin>>n>>p>>s;
	long long ps[p],ss[s];
	for(int i=0;i<p;++i)cin>>ps[i];
	for(int i=0;i<s;++i)cin>>ss[i];
	if(ps[p-1]!=ss[0]||ps[0]!=1||ss[s-1]!=n){
		cout<<0<<'\n';
		return;
	}
	long long ret=1;
	if(ss[0]<n)ret=choose(n-1,ss[0]-1);
// cout<<"first branch: "<<ret<<'\n';
	for(long long i=p-1;i>0;--i){
		long long diff=ps[i]-ps[i-1];
		if(diff>1){
			// handle split
			// multiply by choose(total, dropoff) * fact(dropoff)
			// total=ps[i]-2
			// dropoff=diff-1
			ret=(ret*choose(ps[i]-2,diff-1))%M;
			ret=(ret*fact(diff-1))%M;
		}
	}
	for(long long i=1;i<s;++i){
		long long diff=ss[i]-ss[i-1];
		if(diff>1){
			// total=n-ss[i-1]-1
// cout<<"s between "<<ss[i-1]<<','<<ss[i]<<" choose "<<n-ss[i-1]-1<<','<<diff-1<<'\n';
			ret=(ret*choose(n-ss[i-1]-1,diff-1))%M;
			ret=(ret*fact(diff-1))%M;
		}
	}
	cout<<ret<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
