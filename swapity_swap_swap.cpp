#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;

int main(){
	freopen("swap.in","r",stdin);
	freopen("swap.out","w",stdout);
	int n,m,k,t;
	scanf("%d %d %d",&n,&m,&k);
	int cows[n],a[m],b[m],r[n];
	for(int i=0;i<n;i++)cows[i]=i;
	for(int i=0;i<m;i++){
		scanf("%d %d",&a[i],&b[i]);
		for(int j=-1;j<floor((b[i]-a[i])/(float)2);j++)
			swap(cows[j+a[i]],cows[b[i]-2-j]);
	}
	for(int i=0;i<n;i++)r[cows[i]]=i;
	for(int i=0;i<n;i++){
		t=i;
		for(int j=0;j<k;j++)t=r[t];
		printf("%d\n",1+t);
	}
	return 1;
}
