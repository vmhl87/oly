#include <iostream>
#include <queue>
using namespace std;

int main(){
	int c,n,m,d;cin>>c>>n>>m>>d;
	int wood=0,day=0,plant=0;
	queue<int> growing;
	while(wood<n||!growing.empty()){
		if(!growing.empty()&&growing.front()==day){
// cout<<"harvested a tree\n";
			growing.pop();
			plant++;
		}
		c+=plant;
// cout<<"day "<<day<<", "<<c<<" coconuts\n";
		if(c>0&&wood<n){
// cout<<"planting a new tree\n";
			c--;
			wood++;
			growing.push(day+d);
		}
		day++;
	}
	day--;
	while(c<m){
		c+=plant;
		day++;
	}
	cout<<day<<'\n';
}
