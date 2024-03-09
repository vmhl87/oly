#include <iostream>
#include <algorithm>
using namespace std;

// binary exponentiation
#define M 1000000007
long long exp(long long a,long long p){
	long long ret=1;
	long long A=a;
	for(int i=0;i<31;++i){
		if(p&(1<<i))ret=(ret*A)%M;
		A=(A*A)%M;
	}
	return ret;
}

int main(){
	int n;cin>>n;
	long long t[n];
	for(int i=0;i<n;++i)
		cin>>t[i];
	sort(t,t+n);
// for(long long x:t)cout<<x<<' ';cout<<'\n';
	cout<<exp(t[n-1]+t[0],t[n-1]-t[0])<<'\n';
}
