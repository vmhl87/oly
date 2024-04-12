// Exponentiation II  -  https://cses.fi/problemset/result/8996205/
// Pretty cheesy by binary exp and a bit of number theory

#include <iostream>
using namespace std;

#define MOD 1000000007

// binary exponentiate a^b mod m
long long exp(long long a,long long b,long long m){
	long long ret=1;
	long long i=0;
	while((1<<i)<=b){
		if((1<<i)&b)ret=(ret*a)%m;
		a=(a*a)%m;i++;
	}
	return ret;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;cin>>t;
	while(t-->0){
		int a,b,c;cin>>a>>b>>c;
		// exponentiation of b^c must be mod some integer d
		// such that a^d = 1 mod m -> by fermat's we show d = m-1
		cout<<exp(a,exp(b,c,MOD-1),MOD)<<'\n';
	}
}
