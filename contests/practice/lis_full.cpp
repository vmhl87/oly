#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main(){
	int n;cin>>n;
	// store values
	int a[n];
	// store current sequence
	vector<pair<int,int>> v;
	// backtrace
	vector<int> back(n);
	// main loop - input and process online
	for(int x=0;x<n;++x){
		cin>>a[x];
		// find position to place element
		auto loc=lower_bound(v.begin(),v.end(),make_pair(a[x],0));
		// if place at end, increase length of sequence, and propagate
		// backtrace (current -> vector end OR -1)
		if(loc==v.end()){
			if(v.size())back[x]=v.back().second;
			else back[x]=-1;
			v.push_back(make_pair(a[x],x));
		// otherwise drop in for a value and similarly update backtrace
		}else{
			if(loc==v.begin())back[x]=-1;
			else back[x]=v[(loc-v.begin())-1].second;
			v[loc-v.begin()]=make_pair(a[x],x);
		}
	}
	// output size
	cout<<v.size()<<'\n';
	// traverse though backtrace
	int i=v.back().second;
	stack<int> ret;
	// each processed value is guaranteed to have a parent value, if
	// it is -1, it was placed as the root of the sequence
	while(i>-1){
		ret.push(i);
		i=back[i];
	}
	// sequentially output all
	while(ret.size()){
		cout<<a[ret.top()]<<' ';
		ret.pop();
	}
	cout<<'\n';
}
