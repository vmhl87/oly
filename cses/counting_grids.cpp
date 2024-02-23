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
	sym4=exp(2,quads);
	// count ways with strictly 2-sym
	long long sym2=exp(2,quads*2-1);
	sym2=(sym2-exp(2,quads-1)+MOD)%MOD;
	// count other
	long long sym1=exp(2,quads*4-2);
	sym1=(sym1-exp(2,quads*2-2)+MOD)%MOD;
	// double ways when n is odd
//cout<<"s4: "<<sym4<<"\ns2: "<<sym2<<"\ns1: "<<sym1<<'\n';
	long long ret=(sym1+sym2+sym4)%MOD;
	if(n&1)ret=(ret+ret)%MOD;
	cout<<ret<<'\n';
}
