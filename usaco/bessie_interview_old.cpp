#include <unordered_set>
#include <iostream>
#include <queue>
using namespace std;

vector<int> root;

int findroot(int i){
	queue<int> touch;
	while(root[i]>0){
		touch.push(i);
		i=root[i]-1;
	}
	while(!touch.empty()){
		root[touch.front()]=i+1;
		touch.pop();
	}
	return i;
}

void unify(int a,int b){
	queue<int> touch;
	while(root[a]>0){
		touch.push(a);
		a=root[a]-1;
	}
	while(root[b]>0){
		touch.push(b);
		b=root[b]-1;
	}
	if(b!=a)root[b]=a+1;
	while(!touch.empty()){
		root[touch.front()]=a+1;
		touch.pop();
	}
}

int main(){
	int n,k;cin>>n>>k;
	root.resize(k);
	priority_queue<
		pair<long long,pair<int,int>>,
		vector<pair<long long,pair<int,int>>>,
		greater<pair<long long,pair<int,int>>>
	> farmers;
	for(int i=0;i<k;++i,n--){
		long long t;cin>>t;
		farmers.push(make_pair(t,make_pair(i,1)));
	}
	while(n--){
		long long t,top=farmers.top().first;cin>>t;
		queue<int> group;
		int count=0,cur=-1;
		while(!farmers.empty()&&farmers.top().first==top){
			if(cur<0)cur=farmers.top().second.first;
			if(count)group.push(farmers.top().second.first);
			count+=farmers.top().second.second;
			farmers.pop();
		}
		farmers.push(make_pair(top+t,make_pair(cur,1)));count--;
		if(count==0)continue;
		farmers.push(make_pair(top,make_pair(cur,count)));
		while(!group.empty()){
//cout<<"unify "<<cur<<' '<<group.front()<<'\n';
			unify(cur,group.front());
			group.pop();
		}
//cout<<"time "<<top+t<<'\n';
	}
//cout<<"unions:\n";for(int i=0;i<k;++i)cout<<i<<':'<<findroot(i)<<'\n';
	long long t=farmers.top().first;cout<<t<<'\n';
	unordered_set<int> end;
//if(t==8){cout<<"110\n";return 0;}
	while(!farmers.empty()&&farmers.top().first==t){
		end.insert(farmers.top().second.first);
		farmers.pop();break;
	}
	for(int i=0;i<k;++i)
		cout<<end.count(findroot(i));
	cout<<'\n';
}
