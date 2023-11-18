#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

struct edge{
	short to;
	int r;
};

int main(){
	ifstream cin("mootube.in");
	ofstream cout("mootube.out");
	short n,q;cin>>n>>q;
	vector<struct edge> graph[n];
	for(short i=1;i<n;i++){
		short x,y;int r;cin>>x>>y>>r;
		struct edge tmp;
		tmp.to=y-1;tmp.r=r;
		graph[x-1].push_back(tmp);
		struct edge t2;
		t2.to=x-1;t2.r=r;
		graph[y-1].push_back(t2);
	}
	while(q-->0){
		int k;short v;cin>>k>>v;
		vector<short> frame;frame.push_back(v-1);
		bool visited[n];for(short i=0;i<n;i++)visited[i]=1;visited[v-1]=0;
		int r=0;
		while(frame.size()>0){
			vector<short> next;
			for(short i:frame)
				for(struct edge e:graph[i])
					if(e.r>=k&&visited[e.to]){
						visited[e.to]=0;r++;
						next.push_back(e.to);
					}
			frame.clear();for(short i:next)frame.push_back(i);
		}
		cout<<r<<'\n';
	}
}
