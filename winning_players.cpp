#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
	int n;cin>>n;
	vector<int> ids;
	map<int,int> counts;
	while(n-->0){
		int a,b;cin>>a>>b;
		if(counts.find(a)==counts.end()){counts[a]=0;ids.push_back(a);}
		if(counts.find(b)==counts.end()){counts[b]=1;ids.push_back(b);}
		else counts[b]++;
	}
	vector<int> wins;
	for(int h:ids)if(counts[h]==0)wins.push_back(h);
	sort(wins.begin(),wins.end());
	if(wins.size()){
		for(int h:wins)cout<<h<<' ';cout<<'\n';
	}else cout<<"-1\n";
	return 0;
}

/*
10
1 3
2 3
3 6
5 6
5 7
4 5
4 8
4 9
10 4
10 9
*/
