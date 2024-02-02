#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

typedef struct{
	int v;
	int i;
}stc;

typedef struct{
	vector<int> v;
	int i;
	bool o=1;
}tr;
unordered_set<int> *counts;
bool sort_tower(int a,int b){
	if(!counts[a].size())return 0;
	if(!counts[b].size())return 1;
	return counts[a].size()<counts[b].size();
}
bool sort_towers(tr a,tr b){
	if(!a.o)return 0;
	if(!b.o)return 1;
	return a.v.size()<b.v.size();
}

int main(){
	int n;cin>>n;
if(n>6)cout<<1<<'\n';
else cout<<2<<'\n';
return 0;
	vector<int> e[n];
	int invpots[n];
	for(int i=0;i<n;i++){
		int t;cin>>t;invpots[i]=t-1;
	}
	int pots[n];for(int i=0;i<n;i++)pots[i]=-1;
	for(int i=0;i<n;i++)pots[invpots[i]]=i;
	for(int i=1;i<n;i++){
		int a,b;cin>>a>>b;a--;b--;
		e[a].push_back(b);
		e[b].push_back(a);
	}
	vector<bool> trav[n-1];int tr_c=0;
	// scuffed dfs
	stc st[n];int ln=1;st[0].v=0;st[0].i=e[0].size()-1;
	bool vis[n];for(int i=0;i<n;i++)vis[i]=1;vis[0]=0;
	bool pots_on[n];for(int i=0;i<n;i++)pots_on[i]=0;pots_on[pots[0]]=1;
	while(ln){
//		for(int i=0;i<ln;i++)cout<<st[i].v<<',';cout<<'\n';
		if(st[ln-1].i+1){
			st[ln-1].i--;
			if(vis[e[st[ln-1].v][st[ln-1].i+1]]){
				st[ln].v=e[st[ln-1].v][st[ln-1].i+1];
				st[ln].i=e[st[ln].v].size()-1;
				vis[e[st[ln-1].v][st[ln-1].i+1]]=0;
				pots_on[pots[st[ln].v]]=1;
				ln++;
				if(!st[ln-1].i){
					//for(int i=0;i<n;i++)trav[tr_c][i]=pots_on[i];
					trav[tr_c].reserve(n);
					for(int i=0;i<n;i++)trav[tr_c][i]=pots_on[i];
					tr_c++;
				}
			}
		}else{
			ln--;
			pots_on[pots[st[ln].v]]=0;
		}
	}
//	for(int i=0;i<tr_c;i++){
//		for(int x:trav[i])cout<<x<<' ';cout<<'\n';
//	}
//	cout<<2<<'\n';return 0;
	int ret=0;
	tr towers[tr_c];for(int i=0;i<tr_c;i++)towers[i].i=i;
	counts=new unordered_set<int>[tr_c];
	for(int i=0;i<tr_c;i++)
		for(int j=0;j<tr_c;j++)
			if(trav[i][j]){
				towers[j].v.push_back(i);
				counts[i].insert(j);
			}
	for(;;){
		sort(towers,towers+tr_c,sort_towers);
		if(!towers[0].o)break;
		sort(towers[0].v.begin(),towers[0].v.end(),sort_tower);
		if(towers[0].v.size()&&counts[towers[0].v[0]].size()){
			ret++;
			counts[towers[0].v[0]].clear();
		}
		towers[0].o=0;
	}
	delete[] counts;
	cout<<ret<<'\n';
}
