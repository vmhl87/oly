#include <iostream>
using namespace std;

void test_case(){
	int n,k;cin>>n>>k;
	if(n==1){
		cout<<k<<'\n';
		return;
	}
	int r=(1<<__lg(k))-1;
	cout<<r<<' '<<k-r;
	for(int i=2;i<n;++i)cout<<" 0";
	cout<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
