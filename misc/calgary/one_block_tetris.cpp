#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main(){
	int w,h,n;cin>>w>>h>>n;
	int heights[w],active=0;
	for(int i=0;i<w;++i)heights[i]=0;
	queue<int> ops;int ret=0;
	int cyc=0,len=n;
	for(int i=0;i<n;++i){
		int loc;cin>>loc;
		ops.push(loc);
	}
	while(!ops.empty()){
		int loc=ops.front();
		ops.pop();
		if(heights[loc]==h){
// cout<<"column "<<loc<<" is full\n";
			if(cyc>ops.size()*2){
// cout<<"cycle detected\n";
				cout<<-1<<'\n';
				return 0;
			}
			ret++;
			ops.push(loc);
			cyc++;
			continue;
		}
		cyc=0;
// cout<<"increasing height\n";
		heights[loc]++;
		if(heights[loc]==1){
// cout<<"used to have height 0, growing\n";
			active++;
			if(active==w){
// cout<<"clearing row\n";
				for(int i=0;i<w;++i){
					heights[i]--;
					if(!heights[i])active--;
				}
			}
		}
	}
	cout<<ret<<'\n';
}
