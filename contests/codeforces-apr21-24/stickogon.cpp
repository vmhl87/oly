#include <iostream>
using namespace std;

void test_case(){
	int n;cin>>n;
	int counts[100]={0};
	while(n--){
		int t;cin>>t;
		++counts[t-1];
	}
	int ret=0;
	for(int x:counts)ret+=x/3;
	cout<<ret<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
