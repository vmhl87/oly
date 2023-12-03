#include <iostream>
using namespace std;

void test_case(){
	int a,b;cin>>a>>b;
	if(b>a){
		a=b-a;b-=a;a=b+a;
	}
	if(a*2<b)goto failed;
	a-=b;b-=a;
	if(b<0)goto failed;
	if(b%3>0)goto failed;
	cout<<"YES\n";return;
failed:
	cout<<"NO\n";
}

int main(){
	int n;cin>>n;
	while(n-->0)test_case();
}
