#include <algorithm>
#include <iostream>
using namespace std;

#define M 1000000007

long long inv(long long a,long long p){
	long long p2=1,iter=0,pn=p-2;
	long long pa=a,ret=1;
	while(p2<=pn){
		if(pn&(1<<iter))ret=(ret*pa)%p;
		pa=(pa*pa)%p;
		p2*=2;
		iter++;
	}
	return ret;
}

long long dp[1000001];
bool f[1000001];
long long fact(long long i){
	if(!i)return 1;
	if(i==1)return 1;
	if(f[i])return dp[i];
	int ret=i;
	ret=(ret*fact(i-1))%M;
	f[i]=1;dp[i]=ret;
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
	long long n,k;cin>>n>>k;
	cout<<choose(n,k)<<'\n';
}

int main(){
	int n;cin>>n;
	while(n-->0)test_case();
}
