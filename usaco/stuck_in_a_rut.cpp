#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

typedef struct{
	int x;
	int y;
	int id;
}cow;

typedef struct{
	int time;
	int bound;
	int upper;
	int lower;
}event;

typedef struct{
	int v;
	int w;
}node;

bool comp_e_cows(cow i, cow j){
	return (i.y<j.y);
}

bool comp_n_cows(cow i, cow j){
	return (i.x<j.x);
}

bool comp_events(event i, event j){
	return (i.time<j.time);
}

int main(){
	int n;
	cin>>n;
	vector<cow> e_cows(n);
	vector<cow> n_cows(n);
	int id=0;
	for(int i=0;i<n;i++){
		char c;
		int x,y;
		cin>>c>>x>>y;
		cow tmp;
		tmp.x=x;tmp.y=y;tmp.id=id;
		id++;
		if(c=='E')e_cows.push_back(tmp);
		else n_cows.push_back(tmp);
	}
	vector<event> events;
	for(cow e_cow:e_cows)
		for(cow n_cow:n_cows)
			if(e_cow.x<n_cow.x&&e_cow.y>n_cow.y){
				event tmp;
				if(n_cow.x-e_cow.x<e_cow.y-n_cow.y){
					tmp.time=e_cow.y-n_cow.y;
					tmp.bound=n_cow.x-e_cow.x;
					tmp.upper=e_cow.id;
					tmp.lower=n_cow.id;
				}else if(e_cow.y-n_cow.y<n_cow.x-e_cow.x){
					tmp.time=n_cow.x-e_cow.x;
					tmp.bound=e_cow.y-n_cow.y;
					tmp.upper=n_cow.id;
					tmp.lower=e_cow.id;
				}else continue;
				events.push_back(tmp);
			}
	sort(events.begin(),events.end(),comp_events);
	int ret[n],blame[n];
	stack<int> stops[n];
	bool root[n];
	for(int i=0;i<n;i++){
		ret[i]=-1;
		blame[i]=0;
		root[i]=1;
	}
	for(event e:events){
		if(ret[e.lower]>-1)continue;
		if(ret[e.upper]<0||ret[e.upper]>=e.bound){
			ret[e.lower]=e.time;
			stops[e.upper].push(e.lower);
			root[e.lower]=0;
		}
	}
	for(int i=0;i<n;i++){
		if(root[i]){
			stack<int> dfs;
			dfs.push(i);int t;
			while(!dfs.empty()){
				t=dfs.top();
				if(stops[t].empty()){
					int add=blame[t]+1;
					dfs.pop();
					if(!dfs.empty())blame[dfs.top()]+=add;
				}else{
					int next=stops[t].top();
					stops[t].pop();
					dfs.push(next);
				}
			}
		}
	}
	for(int i=0;i<n;i++)cout<<blame[i]<<'\n';
	return 1;
}
