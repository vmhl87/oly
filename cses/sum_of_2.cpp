#include <algorithm>
#include <iostream>
using namespace std;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,x;cin>>n>>x;
	pair<int,int> a[n];
	for(int i=0;i<n;++i){
		cin>>a[i].first;
		a[i].second=i;
	}
	sort(a,a+n);
	for(int i=0;i<n;++i){
		if((a[i].first<<1)>x)break;
		const auto l=lower_bound(a+i+1,a+n,make_pair(x-a[i].first,0));
		if(l==a+n)continue;
		if(l->first==x-a[i].first){
			cout<<a[i].second+1<<' '<<l->second+1<<'\n';
			return 0;
		}
	}
	cout<<"IMPOSSIBLE\n";
}
