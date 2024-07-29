#include <iostream>
using namespace std;

void test_case(){
	int n,k;cin>>n>>k;
	if(n==k){
		for(int i=0;i<n;++i){
			if(i)cout<<' ';
			cout<<1;
		}
	}else if(k==1){
		for(int i=0;i<n;++i){
			if(i)cout<<' ';
			cout<<i+1;
		}
	}else cout<<-1;
	cout<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
