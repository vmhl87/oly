#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

struct store{
	int wants;
	int pays;
};

bool comp_store(struct store a,struct store b){return a.pays>b.pays;}
bool comp_cow(int a,int b){return a<b;}
bool comp_neighbor(int a,int b){return a>b;}

int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	ifstream cin("rental.in");
	ofstream cout("rental.out");
	int n,m,r;cin>>n>>m>>r;
	int cows[n],neighbors[r];
	struct store stores[m];
	for(int i=0;i<n;i++)cin>>cows[i];
	for(int i=0;i<m;i++)cin>>stores[i].wants>>stores[i].pays;
	for(int i=0;i<r;i++)cin>>neighbors[i];
	sort(cows,cows+n,comp_cow);
	sort(stores,stores+m,comp_store);
	sort(neighbors,neighbors+r,comp_neighbor);
	int out[n];for(int i=0;i<n;i++)out[i]=0;
	int index=n-1;
	for(int i=0;i<m;i++){
		while(stores[i].wants>0){
			if(index<0)break;
			if(stores[i].wants<cows[index]){
				out[index]+=stores[i].pays*stores[i].wants;
				cows[index]-=stores[i].wants;stores[i].wants=0;
			}else{
				out[index]+=stores[i].pays*cows[index];
				stores[i].wants-=cows[index];
				cows[index]=0;index--;
			}
		}
	}
	for(int i=0;i<r;i++){
		if(i==n)break;
		if(neighbors[i]>out[i])out[i]=neighbors[i];
		else break;
	}
	long long total=0;
	for(int i=0;i<n;i++)total+=out[i];
	cout<<total<<'\n';
}
