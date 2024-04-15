#include <stdlib.h>
#include <stdio.h>

int tree[400001][2];
int t[200000];
int n,ln=1;

inline int min(int a,int b){
	return a<b?a:b;
}

inline void prop(int i){
	tree[i][0]=min(tree[i<<1][0],tree[i<<1|1][0]);
	tree[i][1]=min(tree[i<<1][1],tree[i<<1|1][1]);
}

int cmp(const void *a,const void *b){
	return *((int*)a)-*((int*)b);
}

int main(){
	int m;
	scanf("%d %d",&n,&m);
	for(int i=0;i<n;++i)scanf("%d",t+i);
	qsort(t,n,sizeof(int),cmp);
	while(ln<n*2)ln<<=1;
	ln>>=1;
	for(int i=0;i<n;++i){
		int l=i+ln-(i+ln>=n*2)*n;
		tree[l][0]=t[i];
		tree[l][1]=t[i];
	}
	for(int i=n-1;i>0;--i)prop(i);
	while(m--){
		int v;scanf("%d",&v);
		if(v<tree[1][0]){
			printf("-1\n");
			continue;
		}
		int i=1;
		while(i<n){
			if(tree[i<<1|1][0]>v)i<<=1;
			else i=i<<1|1;
		}
		printf("%d\n",tree[i][1]);
		tree[i][0]=1<<30;
		tree[i][1]=-1;
		while(i){
			i>>=1;prop(i);
		}
	}
}
