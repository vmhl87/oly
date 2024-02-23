#include <iostream>
using namespace std;

#define MOD 1000000007

long long exp(long long a,long long b){
	long long ret=1;
	long long i=0;
	while((1<<i)<=b){
		if((1<<i)&b)ret=(ret*a)%MOD;
		a=(a*a)%MOD;i++;
	}
	return ret;
}

int main(){
	int t;cin>>t;
	while(t-->0){
		int a,b;cin>>a>>b;
		cout<<exp(a,b)<<'\n';
	}
}
