#include <unordered_set>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

typedef struct{
	int x;
	int y;
	int p;
	vector<int> to;
}cow;

int main(){
	ifstream cin("moocast.in");
	ofstream cout("moocast.out");
	int n;cin>>n;
	cow cows[n];
	// input cows, square distance
	for(int i=0;i<n;i++){
		cin>>cows[i].x>>cows[i].y>>cows[i].p;
		cows[i].p*=cows[i].p;
	}
	// loop over all pairs of cows:
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			// if distance squared is less than or equal to power, link
			int dist=(cows[i].x-cows[j].x)*(cows[i].x-cows[j].x)+
				(cows[i].y-cows[j].y)*(cows[i].y-cows[j].y);
			if(dist<=cows[i].p)cows[i].to.push_back(j);
			if(dist<=cows[j].p)cows[j].to.push_back(i);
		}
	}
	// create bfs q
	queue<int> bfs;
	int ptr=0,max=0;
	// for every cow:
	while(ptr<n){
		// can reach 1 initially
		int round=1;
		bfs.push(ptr);
		// initialize visited list
		unordered_set<int> vis;
		vis.insert(ptr);
		// bfs:
		while(!bfs.empty()){
			int x=bfs.front();bfs.pop();
			for(int i:cows[x].to){
				if(vis.find(i)==vis.end()){
					vis.insert(i);
					bfs.push(i);
					round++;
				}
			}
		}
		if(round>max)max=round;
		ptr++;
	}
	cout<<max<<'\n';
}
