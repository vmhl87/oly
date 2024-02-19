#include <iostream>
using namespace std;

void test_case(){
	int a=0,b=0;
	for(int i=0;i<5;i++){
		char c;cin>>c;
		if(c=='A')a++;
		else b++;
	}
	if(a>b)cout<<"A\n";
	else cout<<"B\n";
}

int main(){
	int n;cin>>n;
	while(n-->0)test_case();
}
