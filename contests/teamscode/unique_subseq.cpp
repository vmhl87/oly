#include <iostream>
#include <string>
using namespace std;

void test_case(){
	int n,k;cin>>n>>k;k=n-k;
	string s;cin>>s;
	int last[26];for(int i=0;i<26;++i)last[i]=-n;
	for(int i=0;i<n;++i){
		int t=s[i]-'a';
		if(i-last[t]<=k){
			cout<<"No\n";
			return;
		}
		last[t]=i;
	}
	cout<<"Yes\n";
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
