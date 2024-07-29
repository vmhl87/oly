#include <algorithm>
#include <iostream>
using namespace std;

void test_case(){
	int n;cin>>n;
	int c[n];
	for(int i=0;i<n;++i)cin>>c[i];
	sort(c,c+n);
	if(n<2){
		if(c[0]>1)cout<<"NO\n";
		else cout<<"YES\n";
		return;
	}
	if(c[n-1]>c[n-2]+1)cout<<"NO\n";
	else cout<<"YES\n";
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
