#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;

int main(){
	freopen("swap.in","r",stdin);
	freopen("swap.out","w",stdout);
	int n,k,a1,a2,b1,b2;
	scanf("%d %d\n",&n,&k);
	scanf("%d %d\n",&a1,&a2);
	scanf("%d %d",&b1,&b2);
	int cows[n];
	for(int i=0;i<n;i++){
		int c=i;
		if(i>=a1-1&&i<a2)c=a2-1-(i-a1+1);
		if(c>=b1-1&&c<b2)c=b2-1-(c-b1+1);
		cows[i]=c;
	}
	int r[n],loops[n];
	for(int i=0;i<n;i++)r[cows[i]]=i;
	//for(int i=0;i<n;i++)cout<<r[i];cout<<'\n';
	for(int i=0;i<n;i++)loops[i]=0;
	int bound=0;
	while(bound<n){
		int cur=bound;
		vector<int> visited;
		visited.push_back(bound);
		cur=r[cur];
		while(cur!=bound){
			visited.push_back(cur);
			cur=r[cur];
		}
		cur=visited.size();
		//cout<<bound<<':';for(int cow:visited)cout<<cow;cout<<' ';
		for(int cow:visited)loops[cow]=cur;
		bound++;
		for(int i=bound;i<n;i++){
			bound=i;
			if(loops[i]==0)break;
		}
	}
	for(int i=0;i<n;i++){
		int c=i;
		for(int j=0;j<k%loops[i];j++)c=r[c];
		printf("%d\n",c+1);
	}
	return 1;
}
