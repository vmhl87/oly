#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;cin>>n;
	vector<pair<int,int>> m(n);
	for(int i=0;i<n;++i)
		cin>>m[i].second>>m[i].first;
	sort(m.begin(),m.end());
	int t=0,ret=0;
	for(auto l=m.begin();l!=m.end();++l)
		if(l->second>=t){
			++ret;
			t=l->first;
		}
	cout<<ret<<'\n';
}
