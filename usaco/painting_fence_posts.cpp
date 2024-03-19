#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

typedef struct cow{
	int p;
	int i;
	bool operator>(const cow &o)const{
		return p>o.p;
	}
	bool operator<(const cow &o)const{
		return p<o.p;
	}
	bool operator==(const cow &o)const{
		return p==o.p;
	}
}cow;

struct compi{
	bool operator()(const cow &p,const int o)const{
		return p.p<o;
	}
	bool operator()(const int o,const cow &p)const{
		return o<p.p;
	}
};

int main(){
	int n,p;cin>>n>>p;
	int posts[p][2];
	for(int i=0;i<p;++i)
		cin>>posts[i][0]>>posts[i][1];
	unordered_map<int,unordered_map<int,int>> m;
	unordered_map<int,vector<int>> rows,cols;
	unordered_set<int> allrows,allcols;
	for(int i=0;i<p;++i){
		m[posts[i][0]][posts[i][1]]=i;
		cols[posts[i][0]].push_back(posts[i][1]);
		rows[posts[i][1]].push_back(posts[i][0]);
		allcols.insert(posts[i][0]);
		allrows.insert(posts[i][1]);
	}
	for(int row:allrows)sort(rows[row].begin(),rows[row].end());
	for(int col:allcols)sort(cols[col].begin(),cols[col].end());
	int rwalk[p],plen[p],cur=0,last=-1;
	rwalk[0]=0;
	for(int i=1;i<p;++i){
		auto b=upper_bound(cols[posts[cur][0]].begin(),cols[posts[cur][0]].end(),posts[cur][1]);
		if(b!=cols[posts[cur][0]].end()){
			int next=m[posts[cur][0]][*b];
			if(next!=last){
				plen[i]=abs(posts[cur][1]-posts[next][1]);
				last=cur;cur=next;
				rwalk[i]=cur;
				continue;
			}
		}
		b=upper_bound(rows[posts[cur][1]].begin(),rows[posts[cur][1]].end(),posts[cur][0]);
		if(b!=rows[posts[cur][1]].end()){
			int next=m[*b][posts[cur][1]];
			if(next!=last){
				plen[i]=abs(posts[cur][0]-posts[next][0]);
				last=cur;cur=next;
				rwalk[i]=cur;
				continue;
			}
		}
		b=lower_bound(cols[posts[cur][0]].begin(),cols[posts[cur][0]].end(),posts[cur][1]);
		if(b!=cols[posts[cur][0]].begin()){
			int next=m[posts[cur][0]][*(b-1)];
			if(next!=last){
				plen[i]=abs(posts[cur][1]-posts[next][1]);
				last=cur;cur=next;
				rwalk[i]=cur;
				continue;
			}
		}
		b=lower_bound(rows[posts[cur][1]].begin(),rows[posts[cur][1]].end(),posts[cur][0]);
		if(b!=rows[posts[cur][1]].begin()){
			int next=m[*(b-1)][posts[cur][1]];
			if(next!=last){
				plen[i]=abs(posts[cur][0]-posts[next][0]);
				last=cur;cur=next;
				rwalk[i]=cur;
				continue;
			}
		}
	}
	for(int i=0;i<p-1;++i)plen[i]=plen[i+1];
	int psumlen[p+1];psumlen[0]=0;
	for(int i=0;i<p;++i)psumlen[i+1]=psumlen[i]+plen[i];
	if(posts[0][0]==posts[rwalk[p-1]][0])plen[p-1]=abs(posts[0][1]-posts[rwalk[p-1]][1]);
	else plen[p-1]=abs(posts[0][0]-posts[rwalk[p-1]][0]);
	unordered_map<int,vector<cow>> cowrows,cowcols;
	unordered_set<int> crows,ccols;
	int cows[n][4];
	for(int i=0;i<n;++i){
		int x1,y1,x2,y2;cin>>x1>>y1>>x2>>y2;
		cows[i][0]=x1;cows[i][1]=y1;
		cows[i][2]=x2;cows[i][3]=y2;
		if(allcols.find(x1)!=allrows.end()){
			cow c;c.p=y1;c.i=i;
			cowcols[x1].push_back(c);
			ccols.insert(x1);
		}
		if(allrows.find(y1)!=allrows.end()){
			cow c;c.p=x1;c.i=i;
			cowrows[y1].push_back(c);
			crows.insert(y1);
		}
		if(allcols.find(x2)!=allrows.end()){
			cow c;c.p=y2;c.i=-1-i;
			cowcols[x2].push_back(c);
			ccols.insert(x2);
		}
		if(allrows.find(y2)!=allrows.end()){
			cow c;c.p=x2;c.i=-1-i;
			cowrows[y2].push_back(c);
			crows.insert(y2);
		}
	}
	for(int row:crows)sort(cowrows[row].begin(),cowrows[row].end());
	for(int col:ccols)sort(cowcols[col].begin(),cowcols[col].end());
for(int i=0;i<p;++i){if(i)cout<<" -> ("<<plen[i-1]<<") ";cout<<posts[rwalk[i]][0]<<','<<posts[rwalk[i]][1];}cout<<'\n';
	// proc loop - find where cows join/leave in cycle
	int loc[n*2],dist[n*2];
	for(int i=0;i<p;++i){
		int next=(i+1<p?i+1:0);
		// normalize to post indices
		int ii=rwalk[i],nexti=rwalk[next];
		// check if cow join/leave at i
		if(ccols.count(posts[ii][0])){
			auto r=equal_range(cowcols[posts[ii][0]].begin(),cowcols[posts[ii][0]].end(),
					posts[ii][1],compi{});
			for(auto j=r.first;j!=r.second;++j){
				dist[(j->i)+n]=0;
				loc[(j->i)+n]=i+p;
			}
		}
		// check for vertical segment
		if(posts[ii][0]==posts[nexti][0]){
			// search on the column
			if(ccols.count(posts[ii][0])){
				int hi=posts[ii][1],lo=posts[nexti][1];
				if(lo>hi){
					int t=hi;hi=lo;lo=t;
				}
				hi--;lo++;if(lo>hi)continue;
				auto u=upper_bound(cowcols[posts[ii][0]].begin(),cowcols[posts[ii][0]].end(),
						hi,compi{}),
					 l=lower_bound(cowcols[posts[ii][0]].begin(),cowcols[posts[ii][0]].end(),
						lo,compi{});
				for(auto j=l;j!=u;++j){
					dist[(j->i)+n]=abs((j->p)-posts[ii][1]);
					loc[(j->i)+n]=i;
				}
			}
		}else{
			// search on row
			if(crows.count(posts[ii][1])){
				int hi=posts[ii][0],lo=posts[nexti][0];
				if(lo>hi){
					int t=hi;hi=lo;lo=t;
				}
				hi--;lo++;if(lo>hi)continue;
				auto u=upper_bound(cowrows[posts[ii][1]].begin(),cowrows[posts[ii][1]].end(),
						hi,compi{}),
					 l=lower_bound(cowrows[posts[ii][1]].begin(),cowrows[posts[ii][1]].end(),
						lo,compi{});
				for(auto j=l;j!=u;++j){
					dist[(j->i)+n]=abs((j->p)-posts[ii][0]);
					loc[(j->i)+n]=i;
				}
			}
		}
	}
	// setup - find which dir to go
	queue<int> co[p*2];
	for(int i=0;i<n;++i){
		// compare loc[i+n] loc[n-i-1]
		int lo=i+n,hi=n-i-1;
cout<<"cow "<<i<<" ("<<cows[i][0]<<','<<cows[i][1]<<") starts ";
if(dist[lo]){
	cout<<dist[lo]<<" ahead of cycle index "<<loc[lo];
}else{
	cout<<"at cycle index "<<loc[lo]-p;
}
cout<<'\n';
cout<<"cow "<<i<<" ("<<cows[i][2]<<','<<cows[i][3]<<") ends ";
if(dist[hi]){
	cout<<dist[hi]<<" ahead of cycle index "<<loc[hi];
}else{
	cout<<"at cycle index "<<loc[hi]-p;
}
cout<<'\n';
		if(loc[lo]%p>loc[hi]%p){
			int t=hi;hi=lo;lo=t;
		}
	}
	// main loop - iterate over cows in cycle & process cows as we go
	unordered_set<int> carry;
	for(int i=0;i<p;++i){
		// add any cows starting at this post
		// process cows that traveled over this post
		// add any cows ending at this post
		// add cows that join midway
		// add cows that leave midway
	}
}
