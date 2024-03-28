#include <iostream>
using namespace std;

void test_case(){
	int n;cin>>n;
	for(int i=0;i<n;++i)for(int x=0;x<2;++x){
		for(int j=0;j<n;++j){
			if((i^j)&1)cout<<"..";
			else cout<<"##";
		}
		cout<<'\n';
	}
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
