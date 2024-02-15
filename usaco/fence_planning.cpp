#include <fstream>
#include <vector>
#include <queue>
using namespace std;

typedef struct{
	int x;
	int y;
}cow;

int main(){
	ifstream cin("fenceplan.in");
	ofstream cout("fenceplan.out");
	int n,m;cin>>n>>m;
	cow cows[n];
	for(int i=0;i<n;i++)
		cin>>cows[i].x>>cows[i].y;
	vector<int> rel[n];
	for(int i=0;i<m;i++){
		int a,b;cin>>a>>b;a--;b--;
		rel[a].push_back(b);
		rel[b].push_back(a);
	}
	int ptr=0;
	bool vis[n];
	queue<int> q;
	for(int i=0;i<n;i++)vis[i]=0;
	int ret=-1;
	while(ptr<n){
		q.push(ptr);
		int mix=-1,max=-1,miy=-1,may=-1;
		while(!q.empty()){
			int n=q.front();q.pop();
			if(cows[n].x>max)max=cows[n].x;
			if(cows[n].y>may)may=cows[n].y;
			if(cows[n].x<mix||mix<0)mix=cows[n].x;
			if(cows[n].y<miy||miy<0)miy=cows[n].y;
			vis[n]=1;
			for(int i:rel[n])if(!vis[i])q.push(i);
		}
		max-=mix;may-=miy;
		max+=may;max*=2;
		if(max<ret||ret<0)ret=max;
		while(vis[ptr]&&ptr<n)ptr++;
	}
	cout<<ret<<'\n';
}
