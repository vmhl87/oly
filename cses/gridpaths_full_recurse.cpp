#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define M 1000000007

int n,m,ret;

typedef struct tr{
	int x;
	int y;
	int id;
} tr;

vector<tr> traps;
vector<bool> filled;

void rec(vector<int> ts){
	int x=-1,y=-1,e=ts.size()-1,c=0;
	if(e>-1){
		x=traps[ts[e]].x;y=traps[ts[e]].y;
	}
	for(tr t:traps){
		c++;
		if(t.x==x&&t.y==y)continue;
		if(t.x>=x&&t.y>=y){
			ts.push_back(c-1);
			rec(ts);
			ts.pop_back();
		}
	}
	cout<<'-';for(int i:ts)cout<<i<<' ';
	cout<<'\n';
}

int main(){
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int x,y;tr t;cin>>x>>y;
		t.x=x-1;t.y=y-1;t.id=i;
		traps.push_back(t);
		filled.push_back(0);
	}
	ret=1;
	//for(int i=n*2-2;i>n-1;i--)ret*=i;
	//for(int i=n-1;i>1;i--)ret/=i;
	vector<int> v;
	rec(v);
	cout<<ret<<'\n';
}
