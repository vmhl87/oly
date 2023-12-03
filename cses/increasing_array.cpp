#include <iostream>
using namespace std;

int main(){
	long long n,last=0,ret=0;cin>>n;
	while(n-->0){
		long long t;cin>>t;
		if(last>t)ret+=last-t;
		if(t>last)last=t;
	}
	cout<<ret<<'\n';
}
