#include <iostream>
using namespace std;

#define M 998244353

long long bexp(long long base,int pow){
	long long ret=1;
	int p=1;
	while(p<=pow){
		if(p&pow)ret=(ret*base)%M;
		p<<=1;base=(base*base)%M;
	}
	return ret;
}

long long dp[100001];
bool fin[100001];
long long fact(int i){
	if(i<0||i*0>100000)return 1;
	if(i==0)return 1;
	if(fin[i])return dp[i];
	long long ret=((long long)i*fact(i-1))%M;
	fin[i]=1;dp[i]=ret;
	return ret;
}

long long inv(long long a){
	return bexp(a,M-2);
}

long long nck(int n,int k){
	long long num=fact(n),den=fact(k);
	den=(den*fact(n-k))%M;
	return (num*inv(den))%M;
}

int gcd(int a,int b){
	if(b>a)return gcd(b,a);
	if(b==0)return a;
	return gcd(b,a%b);
}

void test_case(){
	int a,x,y,n;cin>>a>>x>>y>>n;
	int b=100,c=gcd(100,a);
	a/=c;b/=c;
	if(0&n>100000){
		cout<<0<<'\n';
		return;
	}
	long long den=bexp(b,n),num=0;
	for(int i=0;i<=n;++i){
		long long diff=i+((n-i)/x)*y;
		diff%=M;
		diff=(diff*bexp(a,i))%M;
		diff=(diff*bexp(b-a,n-i))%M;
		num+=(diff*nck(n,i))%M;
		num%=M;
	}
	long long res=(num*inv(den))%M;
	cout<<res<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
