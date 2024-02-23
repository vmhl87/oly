#include <iostream>
using namespace std;

#define MOD 1000000007

long long exp(long long a,long long pow){
	long long p=1,ret=1;
	while(p<=pow){
		if(pow&p)ret=(ret*a)%MOD;
		p=(p<<1);a=(a*a)%MOD;
	}
	return ret;
}

long long inv(long long i){
	return i;
}

int main(){
	long long n;cin>>n;
	// count ways with 4-symmetry
	long long sym4;
	long long quads;
	if(n&1)quads=(n/2)*(n/2)+n/2;
	else quads=(n/2)*(n/2);
	sym4=exp(2,quads-1);
	// count ways with strictly 2-sym
	long long sym2=exp(2,quads*2-1);
	sym2=(sym2-sym4+MOD)%MOD;
	// count other
	long long ret=exp(16,quads);
	ret=(ret-sym2+MOD)%MOD;
	// double ways when n is odd
	if(n&1)ret=(ret+ret)%MOD;
	cout<<ret<<'\n';
}
