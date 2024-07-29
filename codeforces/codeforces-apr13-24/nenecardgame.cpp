#include <iostream>
using namespace std;

void test_case(){
	int n;cin>>n;
	int count[n];
	for(int i=0;i<n;++i)count[i]=0;
	for(int i=0;i<n;++i){
		int t;cin>>t;--t;
		++count[t];
	}
	int ret=0;
	for(int i=0;i<n;++i)if(count[i]==2)++ret;
	cout<<ret<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
