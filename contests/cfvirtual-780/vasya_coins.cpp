#include <iostream>
using namespace std;

void test_case(){
	int a,b;cin>>a>>b;
	if(a<1){
		cout<<1<<'\n';
		return;
	}
	cout<<a+b+b+1<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
