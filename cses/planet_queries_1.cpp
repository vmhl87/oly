#include <iostream>
#include <vector>
using namespace std;

int main(){
	int n,q;cin>>n>>q;
	int to[n];
	bool vis[n];
	for(int i=0;i<n;++i){
		cin>>to[i];--to[i];
		vis[i]=1;
	}
	int cyc[n],ro[n];
	vector<vector<int>> mp;
	for(int i=0;i<n;++i)if(vis[i]){
		int j=i,c=0;mp.push_back(vector<int>());
		while(to[j]!=i){
			vis[j]=0;
			mp.back().push_back(j);
			ro[j]=mp.size()-1;
			cyc[j]=c;++c;
			j=to[j];
		}
	}
	while(q--){
		int x,k;cin>>x>>k;--x;
		cout<<mp[ro[x]][(cyc[x]+k)%mp[ro[x]].size()]<<'\n';
	}
}
