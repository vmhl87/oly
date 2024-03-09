#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void test_case(){
	int n;cin>>n;
	int val[n];
	for(int i=0;i<n;++i)
		cin>>val[i];
	sort(val,val+n);
	vector<int> adj[n];
	for(int i=0;i<n;++i)
		for(int j=0;j<i;++j)
			if(val[i]%val[j]==0)
				adj[i].push_back(j);
// for(int i=0;i<n;++i){
// 	cout<<val[i]<<" -> ";
// 	for(int x:adj[i])
// 		cout<<val[x]<<' ';
// 	cout<<'\n';
// }
	int ret=0;
	for(int i=0;i<n;++i)
		for(int x:adj[i])
			ret+=adj[x].size();
	cout<<ret<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
