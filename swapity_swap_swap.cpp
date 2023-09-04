#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;

int main(){
	freopen("swap.in","r",stdin);
	freopen("swap.out","w",stdout);
	int n,m,k,t,a,b,bound=0,cur,n_visited;
	scanf("%d %d %d\n",&n,&m,&k);
	int cows[n],visited[n],ret[n];
	bool r[n];
	for(int i=0;i<n;i++){
		cows[i]=i;l[i]=0;r[i]=true;
	}
	for(int i=0;i<m;i++){
		scanf("%d %d",&a,&b);
		for(int j=-1;j<floor((b-a)/(float)2);j++)
			swap(cows[j+a],cows[b-2-j]);
	}
	//for(int i=0;i<n;i++)cout<<cows[i];cout<<'\n';return 1;
	while(bound<n){
		cur=cows[bound];n_visited=1;
		visited[0]=bound;
		while(cur!=bound){
			visited[n_visited]=cur;
			n_visited++;
			cur=cows[cur];
		}
		int shift=k%n_visited;
		for(int i=0;i<n_visited;i++){
			r[visited[i]]=false;
			ret[visited[i]]=visited[(i+shift)%n_visited];
		}
		bound++;
		for(int i=bound;i<n;i++){
			bound=i;
			if(r[i])break;
		}
	}
	for(int i=0;i<n;i++){
		printf("%d\n",ret[i]+1);
	}
	return 1;
}
