#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct tr{
	int x;
	int y;
	int id;
	int block=0;
	vector<int>
} tr;

typedef struct xy{
	int id;
	int xy;
} xy;

bool diag(tr a,tr b){
	return a.x+a.y<b.x+b.y;
}

bool compxy(xy a,xy b){
	return a,xy<b.xy;
}

int main(){
	vector<tr> traps;
	vector<xy> xs,ys;
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int t,r;cin>>t>>r;
		tr tmp;tmp.x=t;tmp.y=r;tmp.id=i;
		xy x,y;x.id=i;y.id=i;x.xy=t;y.xy=r;
		traps.push_back(tr);xs.push_back(x);ys.push_back(y);
	}
	sort(xs.begin(),xs.end(),compxy);
	sort(ys.begin(),ys.end(),compxy);
	for(int i=0;i<m;i++){
		bool r[m];for(int h=0;h<m;h++)r[h]=0;
		
	}
	sort(traps.begin(),traps.end(),diag);
}
