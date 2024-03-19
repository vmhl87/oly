#include <iostream>
#include <queue>
#include <set>
#include <map>
using namespace std;

int main(){
	int n,k;cin>>n>>k;
	priority_queue<
		pair<long long,pair<int,int>>,
		vector<pair<long long,pair<int,int>>>,
		greater<pair<long long,pair<int,int>>>
	> farmers;
	map<int,long long> id;
	map<long long,set<int>> back;
	for(int i=0;i<k;++i,--n){
		long long j;cin>>j;
		id[i]=0;back[j].insert(i);
		farmers.push(make_pair(j,make_pair(i,1)));
	}
	int idx=k;
	while(n--){
		long long t,top=farmers.top().first;cin>>t;
		int count=0,cur=farmers.top().second.first;queue<int> group;
		while(farmers.size()&&farmers.top().first==top){
			group.push(farmers.top().second.first);
			count+=farmers.top().second.second;
			farmers.pop();
		}
		id[idx]=top;farmers.push(make_pair(top+t,make_pair(idx++,1)));
		if(count>1)farmers.push(make_pair(top,make_pair(cur,count-1)));
		while(group.size()){
			back[top+t].insert(group.front());group.pop();
		}
	}
	long long t=farmers.top().first;cout<<t<<'\n';
	set<long long> vis;set<int> end;queue<long long> bfs;bfs.push(t);
	while(bfs.size()){
		int top=bfs.front();bfs.pop();
		for(int x:back[top])
			if(!end.count(x)){
				end.insert(x);
				if(!vis.count(id[x])){
					vis.insert(id[x]);bfs.push(id[x]);
				}
			}
	}
	for(int i=0;i<k;++i)
		cout<<end.count(i);
	cout<<'\n';
}
