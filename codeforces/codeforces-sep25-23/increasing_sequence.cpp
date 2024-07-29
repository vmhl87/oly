#include <iostream>
using namespace std;

void test_case(){
	int n;cin>>n;
	int cur=0,t;
	for(int i=0;i<n;i++){
		cin>>t;
		cur++;if(cur==t)cur++;
	}
	cout<<cur<<'\n';
}

int main(){
	int c;cin>>c;
	while(c-->0)test_case();
	return 0;
}
