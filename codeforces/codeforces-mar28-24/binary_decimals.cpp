#include <iostream>
#include <stack>
using namespace std;

bool isbindec(int n){
	while(n){
		if(n%10>1)return 0;
		n/=10;
	}
	return 1;
}

bool dp[100001];
bool fi[100001];
bool possible(int n){
	if(isbindec(n))return 1;
	if(fi[n])return dp[n];
	bool ret=0;
	for(int i=2;i*i<=n;++i)if(n%i==0){
		if(isbindec(i))ret|=possible(n/i);
		if(isbindec(n/i))ret|=possible(i);
	}
	fi[n]=1;dp[n]=ret;
	return ret;
}

void test_case(){
	int n;cin>>n;
	if(possible(n))cout<<"YES\n";
	else cout<<"NO\n";
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
