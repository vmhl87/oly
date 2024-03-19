#include <iostream>
#include <queue>
using namespace std;

vector<int> root;

int findroot(int i){
	queue<int> touch;
	while(root[i]>-1){
		touch.push(i);
		i=root[i];
	}
	while(!touch.empty()){
		root[touch.front()]=i;
		touch.pop();
	}
	return i;
}

void unify(int a,int b){
	queue<int> touch;
	while(root[a]>-1){
		touch.push(a);
		a=root[a];
	}
	while(root[b]>-1){
		touch.push(b);
		b=root[b];
	}
	if(b!=a)root[b]=a;
	while(!touch.empty()){
		root[touch.front()]=a;
		touch.pop();
	}
}

int main(){
	int n,k;cin>>n>>k;
	root.resize(k,-1);
	priority_queue<
		pair<long long,pair<int,int>>,
		vector<pair<long long,pair<int,int>>>,
		greater<pair<long long,pair<int,int>>>
	> farmers;
	for(int i=0;i<k;++i,--n){
		long long j;cin>>j;
		farmers.push(make_pair(j,make_pair(i,1)));
	}
	while(n--){
		long long t,top=farmers.top().first;cin>>t;
		queue<int> group;
		int count=0,cur=farmers.top().second.first;
		while(!farmers.empty()&&farmers.top().first==top){
			group.push(farmers.top().second.first);
			count+=farmers.top().second.second;
			farmers.pop();
		}
		farmers.push(make_pair(top+t,make_pair(cur,1)));
		if(count>1)farmers.push(make_pair(top,make_pair(cur,count-1)));
		while(!group.empty()){
			unify(cur,group.front());
			group.pop();
		}
	}
//cout<<"unions:\n";for(int i=0;i<k;++i)cout<<i<<':'<<findroot(i)<<'\n';
	cout<<farmers.top().first<<'\n';
	int end=findroot(farmers.top().second.first);
	for(int i=0;i<k;++i)
		cout<<(end==findroot(i));
	cout<<'\n';
}
