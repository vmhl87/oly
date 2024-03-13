#include <fstream>
#include <vector>
#include <stack>
#include <map>
using namespace std;

struct field{
	int comp=-1;
	// up, down, left, right
	bool road[4]={0,0,0,0};
	stack<pair<int,int>> adj;
};

int main(){
	ifstream cin("countcross.in");
	ofstream cout("countcross.out");
	int n,k,r;cin>>n>>k>>r;
	field fields[n][n];
	// read in roads
	for(int i=0;i<r;++i){
		int r,c,rr,cc;cin>>r>>c>>rr>>cc;
		r--;c--;rr--;cc--;
		if(rr>r){
			fields[r][c].road[1]=1;
			fields[rr][c].road[0]=1;
		}
		if(rr<r){
			fields[r][c].road[0]=1;
			fields[rr][c].road[1]=1;
		}
		if(cc>c){
			fields[r][c].road[3]=1;
			fields[r][cc].road[2]=1;
		}
		if(cc<c){
			fields[r][c].road[2]=1;
			fields[r][cc].road[3]=1;
		}
	}
	// fill in adj
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j){
			if(i>0&&!fields[i][j].road[0])
				fields[i][j].adj.push(make_pair(i-1,j));
			if(i<n-1&&!fields[i][j].road[1])
				fields[i][j].adj.push(make_pair(i+1,j));
			if(j>0&&!fields[i][j].road[2])
				fields[i][j].adj.push(make_pair(i,j-1));
			if(j<n-1&&!fields[i][j].road[3])
				fields[i][j].adj.push(make_pair(i,j+1));
		}
	int comp=0;
	pair<int,int> p(0,0);
	stack<pair<int,int>> dfs;
	while(p.second<n){
		if(fields[p.first][p.second].comp<0){
			dfs.push(p);
			fields[p.first][p.second].comp=comp;
			while(!dfs.empty()){
				pair<int,int> top=dfs.top();
				if(fields[top.first][top.second].adj.empty()){
					dfs.pop();continue;
				}
				pair<int,int> next=fields[top.first][top.second].adj.top();
				if(fields[next.first][next.second].comp<0){
					fields[next.first][next.second].comp=comp;
					dfs.push(next);
				}
				fields[top.first][top.second].adj.pop();
			}
			comp++;
		}
		p.first++;
		if(p.first==n){
			p.first=0;
			p.second++;
		}
	}
// for(int i=0;i<n;++i){
// 	for(field x:fields[i]){
// 		for(bool y:x.road)cout<<y;
// 		cout<<' ';
// 	}
// 	cout<<'\n';
// }
// for(int i=0;i<n;++i){
// 	for(field x:fields[i])
// 		cout<<x.comp<<' ';
// 	cout<<'\n';
// }
	map<int,int> cows;
	for(int i=0;i<k;++i){
		int r,c;cin>>r>>c;r--;c--;
		int cow=fields[r][c].comp;
		if(cows.find(cow)==cows.end())cows[cow]=1;
		else cows[cow]++;
	}
	vector<int> counts(cows.size());
	int idx=0;
	for(auto [comp,count]:cows){
// cout<<count<<' ';
		counts[idx]=count;
		idx++;
	}
// cout<<'\n';
	int ret=0;
	for(int i=0;i<counts.size();++i)
		for(int j=i+1;j<counts.size();++j)
			ret+=counts[i]*counts[j];
	cout<<ret<<'\n';
}
