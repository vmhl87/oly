#include <iostream>
using namespace std;

int main(){
	int n,q;cin>>n>>q;
	long long p[n+1];p[0]=0;
	for(int i=0;i<n;++i){
		long long t;cin>>t;
		p[i+1]=p[i]+t;
	}
	for(int i=0;i<q;i++){
		int a,b;cin>>a>>b;
		cout<<p[b]-p[a-1]<<'\n';
	}
}
