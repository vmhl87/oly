#include <iostream>
using namespace std;

void pri(int n){
	if(n<10)cout<<0;
	cout<<n;
}

void test_case(){
	int h,m;char t;
	cin>>h>>t>>m;
	if(h==0)cout<<12;
	else if(h>12)pri(h-12);
	else pri(h);
	cout<<':';
	pri(m);
	if(h>11)cout<<" PM\n";
	else cout<<" AM\n";
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
