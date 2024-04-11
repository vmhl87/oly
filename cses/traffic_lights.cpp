#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

int main(){
	int x,n;cin>>x>>n;
	multiset<int> len;
	len.insert(x);
	set<int> bounds;
	bounds.insert(0);
	bounds.insert(x);
	while(n--){
		int p;cin>>p;
		auto ub=upper_bound(bounds.begin(),bounds.end(),p);
		int u=*ub,l=*(--ub);
		bounds.insert(p);
		int ln=u-l;len.erase(len.find(ln));
		len.insert(u-p);
		len.insert(p-l);
		cout<<*(--len.end())<<' ';
	}
	cout<<'\n';
}
