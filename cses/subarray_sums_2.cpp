#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main(){
	int n,x;cin>>n>>x;
	vector<int> a;
	a.reserve(n+1);
	a.push_back(0);
	for(int i=0;i<n;i++){
		int t;cin>>t;
		a.push_back((a[i]+t)%x);
	}
	sort(a.begin(),a.end());
	int ret=0;
	for(int i=0;i<n;i++){
		int lbound=lower_bound(a.begin(),a.end(),a[i])-a.begin(),
			ubound=upper_bound(a.begin(),a.end(),a[i])-a.begin();
		ret+=ubound-lbound;
	}
	cout<<ret<<'\n';
}
