#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;cin>>n;
	int r[n]; for(int i=0; i<n; ++i) cin >> r[i];
	multiset<int> towers;
	for(int c : r){
		auto bound=towers.upper_bound(c);
		if(bound!=towers.end())
			towers.erase(bound);
		towers.insert(c);
	}
	cout<<towers.size()<<'\n';
}
