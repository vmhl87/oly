#include <iostream>
using namespace std;

typedef struct{
	int count=1;
	int val=0;
	int nextx,nexty;
	bool end=1;
}cell;

int main(){
	int n;cin>>n;
	cell board[n+1][n+1];
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			char c;cin>>c;
			if(c=='R'){
				board[i][j].nextx=j+1;
				board[i][j].nexty=i;
			}else{
				board[i][j].nextx=j;
				board[i][j].nexty=i+1;
			}
		}
		int c;cin>>c;
		board[i][n].val=c;
		board[i][n].count=0;
	}
	for(int i=0;i<n;++i){
		int c;cin>>c;
		board[n][i].val=c;
		board[n][i].count=0;
	}
	board[n][n].count=0;
	int p=0;
	while(p<n*n){
		int i=p/n,j=p%n;
		if(board[i][j].end){
			while(!board[i][j].val){
				board[i][j].end=0;
				int ni=board[i][j].nexty,
					nj=board[i][j].nextx;
				board[ni][nj].count+=board[i][j].count;
				i=ni,j=nj;
			}
		}
		p++;
	}
/*
for(int i=0;i<n+1;++i){
	for(int j=0;j<n+1;++j)
		cout<<board[i][j].count;
	cout<<'\n';
}
*/
	int cost=0;
	for(int i=0;i<n;++i)cost+=board[n][i].val*board[n][i].count;
	for(int i=0;i<n;++i)cost+=board[i][n].val*board[i][n].count;
	cout<<cost<<'\n';
	int q;cin>>q;
	while(q-->0){
		int a,b;cin>>a>>b;a--;b--;
		
	}
}
