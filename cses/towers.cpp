#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

int main(){
	int n;cin>>n;
	int ret=0;
	multiset<int> towers;
	for(int i=0;i<n;i++){
		int c;
		cin>>c;
		auto lbound=lower_bound(towers.begin(),towers.end(),c+1);
		if(lbound==towers.end()){
//cout<<"making new tower for "<<c<<'\n';
			towers.insert(c);
			ret++;
		}else{
//cout<<"advancing tower "<<*lbound<<" to "<<c<<'\n';
			towers.erase(lbound);
			towers.insert(c);
		}
	}
	cout<<ret<<'\n';
}
