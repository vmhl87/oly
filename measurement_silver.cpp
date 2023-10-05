#include <algorithm>
#include <map>
#include <bits/stdc++.h>
using namespace std;

struct cow{
	int day;
	int cow;
	int change;
};

bool comp_cows(struct cow a, struct cow b){
	return a.day<b.day;
}

int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	ifstream cin("measurement.in");
	ofstream cout("measurement.out");
	int n,g;cin>>n>>g;
	struct cow events[n];
	map<int,int> indexmap;
	int index=0;
	for(int i=0;i<n;i++){
		int day,cow,change;
		char t;cin>>day>>cow>>t>>change;
		if(!indexmap.count(cow)){
			indexmap[cow]=index;
			index++;
		}
		events[i].day=day;events[i].cow=indexmap[cow];
		if(t=='-')events[i].change=-change;
		else events[i].change=change;
	}
	int levels[index+1];
	sort(events,events+n,comp_cows);
	bool leaderboard[index+1],next[index+1];
	for(int i=0;i<index+1;i++){
		levels[i]=0;leaderboard[i]=true;
	}
	int ret=0,cowsInLeaderboard=index+1;
	for(struct cow c:events){
		levels[c.cow]+=c.change;
		if(c.change>0||leaderboard[c.cow]){
			if(c.change<0&&cowsInLeaderboard>1){
				leaderboard[c.cow]=false;
				cowsInLeaderboard--;
				ret++;
				continue;
			}
			if(c.change>0&&leaderboard[c.cow]){
				if(cowsInLeaderboard==1)continue;
				for(int i=0;i<index+1;i++)leaderboard[i]=(i==c.cow);
				cowsInLeaderboard=1;
				ret++;
				continue;
			}
			int maxOutput=0;
			for(int i=0;i<index;i++)
				if(maxOutput<levels[i])maxOutput=levels[i];
			for(int i=0;i<index+1;i++)
				next[i]=(maxOutput==levels[i]);
			bool change=0;
			cowsInLeaderboard=0;
			for(int i=0;i<index+1;i++){
				if(next[i]!=leaderboard[i])change=1;
				leaderboard[i]=next[i];
				if(next[i])cowsInLeaderboard++;
			}
			if(change)ret++;
		}
	}
	cout<<ret<<'\n';
}
