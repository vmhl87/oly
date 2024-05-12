#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(NULL);
	int x,n;cin>>x>>n;
	multiset<int> len;
	len.insert(x);
	set<int> bounds;
	bounds.insert(0);
	bounds.insert(x);
	while(n--){
		int p;cin>>p;
		auto ub=bounds.upper_bound(p);
		int u=*ub,l=*(--ub);
		bounds.insert(p);
		int ln=u-l;len.erase(len.find(ln));
		len.insert(u-p);
		len.insert(p-l);
		cout<<*(--len.end())<<' ';
	}
	cout<<'\n';
}
