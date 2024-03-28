#include <iostream>
using namespace std;

void test_case(){
	int a,b,c;cin>>a>>b>>c;
	if(a<b&&b<c)cout<<"STAIR\n";
	else if(a<b&&b>c)cout<<"PEAK\n";
	else cout<<"NONE\n";
}

int main(){
	int n;cin>>n;
	while(n--)test_case();
}
