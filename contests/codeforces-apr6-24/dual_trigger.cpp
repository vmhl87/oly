#include <iostream>
using namespace std;

void test_case(){
	int n;cin>>n;
	int p1=-1,p2=-1,count=0;
	while(n--){
		char c;cin>>c;
		if(c=='1'){
			++count;
			if(p1<0)p1=n;
			else if(p2<0)p2=n;
		}
	}
	if(count&1){
		cout<<"NO\n";
		return;
	}
	if(p1==p2+1&&count==2)cout<<"NO\n";
	else cout<<"YES\n";
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
