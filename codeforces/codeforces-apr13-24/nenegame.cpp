#include <iostream>
#include <algorithm>
using namespace std;

void test_case(){
	int k,q;cin>>k>>q;
	int a[k];for(int i=0;i<k;++i)cin>>a[i];
	for(int i=0;i<q;++i){
		if(i)cout<<' ';
		int t;cin>>t;
		cout<<min(t,a[0]-1);
	}
	cout<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
