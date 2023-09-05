#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct cow{
	int x;
	int y;
	int id;
};

struct event{
	int time;
	int bound;
	int upper;
	int lower;
};

bool comp_e_cows(struct cow i, struct cow j){
	return (i.y<j.y);
}

bool comp_n_cows(struct cow i, struct cow j){
	return (i.x<j.x);
}

bool comp_events(struct event i, struct event j){
	return (i.time<j.time);
}

int main(){
	int n;
	cin>>n;
	vector<struct cow> e_cows;
	vector<struct cow> n_cows;
	int id=0;
	for(int i=0;i<n;i++){
		char c;
		int x,y;
		cin>>c>>x>>y;
		struct cow tmp;
		tmp.x=x;tmp.y=y;tmp.id=id;
		id++;
		if(c=='E')e_cows.push_back(tmp);
		else n_cows.push_back(tmp);
	}
	vector<struct event> events;
	for(struct cow e_cow:e_cows)
		for(struct cow n_cow:n_cows)
			if(e_cow.x<n_cow.x&&e_cow.y>n_cow.y){
				struct event tmp;
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
	int ret[n];
	for(int i=0;i<n;i++)ret[i]=-1;
	for(struct event e:events){
		if(ret[e.lower]>-1)continue;
		if(ret[e.upper]==-1||ret[e.upper]>=e.bound)
			ret[e.lower]=e.time;
	}
	for(int i=0;i<n;i++){
		if(ret[i]==-1)cout<<"Infinity\n";
		else cout<<ret[i]<<'\n';
	}
	return 1;
}
