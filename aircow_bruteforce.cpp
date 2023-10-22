#include <iostream>
using namespace std;

struct cow{
	int start;
	int end;
	int amount;
};

struct con{
	int start;
	int end;
	int amount;
	int cost;
};

int main(){
	int n,m,mincost=0;cin>>n>>m;
	struct cow cows[n];
	struct con cons[m];
	for(int i=0;i<n;i++){
		int s,e,c;cin>>s>>e>>c;
		cows[i].start=s-1;cows[i].end=e-1;cows[i].amount=c;
	}
	for(int i=0;i<m;i++){
		int s,e,c,m;cin>>s>>e>>c>>m;mincost+=m;
		cons[i].start=s-1;cons[i].end=e-1;cons[i].amount=c;cons[i].cost=m;
	}
	int target=1;for(int i=0;i<m;i++)target*=2;
	for(int i=0;i<target;i++){
		int cost=0,vals[100];
		for(int j=0;j<100;j++)vals[j]=0;
		for(int j=0;j<m;j++){
			if(i&(1<<j)){
				cost+=cons[j].cost;
				for(int k=cons[j].start;k<=cons[j].end;k++)
					vals[k]+=cons[j].amount;
			}
		}
		for(int j=0;j<n;j++)
			for(int k=cows[j].start;k<=cows[j].end;k++)
				if(vals[k]<cows[j].amount)goto failed;
		if(cost>0&&cost<mincost)mincost=cost;
		failed: continue;
	}
	cout<<mincost<<'\n';
	return 0;
}
