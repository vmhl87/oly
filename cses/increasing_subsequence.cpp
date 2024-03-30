#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main(){
	int n;cin>>n;
	vector<int> seq;
	while(n--){
		int v;cin>>v;
		auto i=lower_bound(seq.begin(),seq.end(),v);
		if(i==seq.end())seq.push_back(v);
		else seq[i-seq.begin()]=v;
	}
	cout<<seq.size()<<'\n';
}
